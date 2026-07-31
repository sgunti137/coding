/*
 * @lc app=leetcode id=3016 lang=cpp
 *
 * [3016] Minimum Number of Pushes to Type Word II
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        vector<int> cnt(26);
        for (int i = 0; i < n; ++i) {
            cnt[word[i] - 'a']++;
        }
        sort(cnt.begin(), cnt.end());
        reverse(cnt.begin(), cnt.end());

        int cur_num_id = 1, num = 1;

        int ans = 0;
        for (int i = 0; i < 26; ++i) {

            if (cnt[i] == 0) break;

            ans += (cur_num_id * cnt[i]);
            num++;

            if (num == 9) {
                num = 1;
                cur_num_id++;
            }
        }
        return ans;
    }
};
// @lc code=end

