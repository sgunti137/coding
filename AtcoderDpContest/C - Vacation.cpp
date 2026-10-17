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
	vector<int> a(n), b(n), c(n);

	for (int i = 0; i < n; ++i) {
		cin >> a[i] >> b[i] >> c[i];
	}

	// what is important? current_index, what he has done on last day!
	// dp[index][prev_activity]
	// answer is max of dp[n - 1][0], dp[n-1][1], dp[n-1][2]
	// we do not need N*3 space, we can reuse the space!
	
	vector<int> dp(3, 0);
	dp[0] = a[0]; dp[1] = b[0]; dp[2] = c[0];
	for (int i = 1; i < n; ++i) {
		vector<int> new_dp(3, 0);
		
		new_dp[0] = a[i] + max(dp[1], dp[2]);
		new_dp[1] = b[i] + max(dp[0], dp[2]);
		new_dp[2] = c[i] + max(dp[0], dp[1]);

		dp = new_dp;
	}

	cout << max({dp[0], dp[1], dp[2]}) << endl;
}
