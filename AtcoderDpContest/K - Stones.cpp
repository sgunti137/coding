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

void dfs (int node, vector<int>& dp, vector<int>& a) {
	for (int i = 0; i < a.size(); ++i) {
		if (node >= a[i]) {
			if (dp[node] + 1 < dp[node - a[i]]) {
				dp[node - a[i]] = min(dp[node] + 1, dp[node - a[i]]);
				dfs(node - a[i], dp, a);
			}
		}
	}
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n);
	for (auto& x: a) cin >> x;

	vector<int> dp(1e5 + 5, INT_MAX);
	dp[k] = 0;

	dfs(k, dp, a);

	int mi = INT_MAX;
	for (auto x: a) mi = min(x, mi);

	bool odd = 0;
	for (int i = 0; i < mi; ++i) {
		if (dp[i] % 2) odd = 1;
	}
	cout << (odd ? "First" : "Second") << endl;
}
