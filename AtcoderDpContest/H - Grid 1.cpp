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

const int mod = 1e9 + 7;

int main() {
	int n, m;
	cin >> n >> m;
	vector<string> grid(n);

	for (int i = 0; i < n; ++i) {
		cin >> grid[i];
	}

	vector<vector<int>> dp(n, vector<int> (m, 0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (grid[i][j] == '#') continue;
			if (i == 0 && j == 0) {
				dp[i][j] = 1;
			} else if (i == 0) {
				dp[i][j] = dp[i][j - 1] % mod;
			} else if (j == 0) {
				dp[i][j] = dp[i - 1][j] % mod;
			} else {
				dp[i][j] = (dp[i - 1][j] % mod + dp[i][j - 1] % mod) % mod;
			}
		}
	}

	cout << dp[n - 1][m - 1] << endl;
}
