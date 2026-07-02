/*
 * @lc app=leetcode id=1967 lang=cpp
 *
 * [1967] Number of Strings That Appear as Substrings in Word
 */
using namespace std;
// @lc code=start
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int ans = 0;
        for (int i = 0; i < patterns.size(); ++i) {
            bool ok = 0;
            for (int j = 0; j < word.size(); ++j) {
                if (j + patterns[i].size() <= word.size() && word.substr(j, patterns[i].size()) == patterns[i]) {
                    ok = 1;
                }
            }
            if (ok) ans++;
        }

        return ans;
    }
};
// @lc code=end

