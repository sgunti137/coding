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
	string a, b;
	cin >> a >> b;

	int n = a.size(), m = b.size();

	vector<vector<int>> dp(n, vector<int>(m, 0));

	for (int i = n - 1; i >= 0; --i) {
		for (int j = m - 1; j >= 0; --j) {
			if (i == n - 1 && j == m - 1) {
				dp[i][j] = (a[n - 1] == b[m - 1] ? 1 : 0);
			} else if (i == n - 1) {
				dp[i][j] = (a[i] == b[j] ? 1 : dp[i][j + 1]);
			} else if (j == m - 1) {
				dp[i][j] = (a[i] == b[j] ? 1 : dp[i + 1][j]);
			} else {
				if (a[i] == b[j]) {
					dp[i][j] = 1 + dp[i + 1][j + 1];
				} else {
					dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
				}
			}
		}
	}

	// debug() << imie(dp);

	// feed forward for the answer
	string answer = "";
	int cur = dp[0][0];
	int ap = 0, bp = 0;

	while (cur > 0 && ap < n && bp < m) {
		if (a[ap] == b[bp]) {
			cur--;
			answer += a[ap];
			ap++;
			bp++;
		} else {
			if (cur == dp[ap][bp + 1]) {
				bp++;
			} else {
				ap++;
			}
		}
	}

	cout << answer << endl;
}
