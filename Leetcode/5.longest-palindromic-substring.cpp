// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
		int st = 0, len = 1;

		for (int i = 0; i < n; ++i) {
			int l = i - 1, r = i + 1, cur = 1;
			while (l >= 0 && r < n) {
				if (s[l] == s[r]) {
					cur += 2;
					if (cur > len) {
						len = cur;
						st = l;
					}
					l--;
					r++;
				} else break;
			}

			l = i; r = i + 1; cur = 0;
			while (l >= 0 && r < n) {
				if (s[l] == s[r]) {
					cur += 2;
					if (cur > len) {
						len = cur;
						st = l;
					}
					l--;
					r++;
				} else break;
			}
		}

		return s.substr(st, len);
    }
};
// @leet end
