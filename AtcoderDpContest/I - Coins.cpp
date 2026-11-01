#include <iomanip>
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
}

int main() {
	int n;
	cin >> n;

	vector<double> p(n);
	for (auto& x: p) cin >> x;

	vector<double> dp(n + 1, 0.0);
	dp[0] = 1 - p[0]; // getting a tail on first coin flip
	dp[1] = p[0]; // get a head on first coin flip 
	
	for (int i = 1; i < n; ++i) {
		vector<double> new_dp(n + 1, 0.0);
		for (int heads = 0; heads <= n; ++heads) {
			new_dp[heads] = dp[heads] * (1 - p[i]);
			if (heads > 0) {
				new_dp[heads] += dp[heads - 1] * (p[i]);
			}
		}
		dp = new_dp;
	}

	double ans = 0.0;

	for (int i = 0; i < n + 1; ++i) {
		if (i > n - i) {
			ans += dp[i];
		}
	}

	cout << setprecision(10) << ans << endl;
}
