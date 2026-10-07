// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
		map<char, int> f;

		int ans = 0, len = 0, left = 0;
		for (int i = 0; i < n; ++i) {
			f[s[i]]++;
			len++;
			while (f[s[i]] > 1) {
				len--;
				f[s[left]]--;
				left++;
			}
			ans = max(ans, len);
		}

		return ans;
    }
};
// @leet end
