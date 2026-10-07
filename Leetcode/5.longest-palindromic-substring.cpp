// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
		int st = -1, len = 0;

		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				bool ok = 1;
				for (int k = i; k <= j; k++) {
					if (s[k] != s[j - i + 1 + k - 1]) {
						ok = 0;
					}
				}
				if (ok && j - i + 1 > len) {
					st = i; len = j - i + 1;
				}
			}
		}

		return s.substr(st, len);
    }
};
// @leet end
