#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <iterator>
#include <string>
#include <limits>
#include <complex>
#include <random>
#include <chrono>

using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifndef ONLINE_JUDGE
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

void test_case() {
	long long n, q;
	cin >> n >> q;
	vector<long long> a(n);
	long long ma = LLONG_MIN, mi = LLONG_MAX;

	for (long long i = 0; i < n; ++i) {
		cin >> a[i];
		ma = max(ma, a[i]);
		mi = min(mi, a[i]);
	}

	vector<long long> d;
	d.push_back(ma - mi);

	vector<long long> cur = a;
	int CAP = 150;	
	int steps = 0;
	while (d.back() != 0 && steps < CAP) {
		int m = cur.size();
		vector<long long> xs;
		
		for (int i = 0; i < m; i++) {
			for (int j = i+1; j < m; j++) {
				xs.push_back(cur[i] ^ cur[j]);
			}
		}
		
		nth_element(xs.begin(), xs.begin() + (m-1), xs.end());
		sort(xs.begin(), xs.begin() + m);
		
		cur.assign(xs.begin(), xs.begin() + m);
		
		long long ma = *max_element(cur.begin(), cur.end());
		long long mi = *min_element(cur.begin(), cur.end());
		
		d.push_back(ma - mi);
		steps++;
	}

	for (int i = 0; i < q; i++){
		long long x;
		cin >> x;
		
		long long ans = (x < (long long)d.size()) ? d[x] : 0;
		cout << ans << endl;
	}
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
	return 0;
}
