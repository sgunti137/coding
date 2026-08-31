/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        set<vector<int>> res;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int sel = 0; sel < pow(2, n); ++sel) {
            vector<int> s(n, 0);
            int id = 0, sel2 = sel;
            while (sel2 > 0) {
                assert(id < n);
                if (sel2 % 2 == 1) {
                    s[id] = 1;
                }
                sel2 /= 2;
                id++;
            }

            vector<int> r;
            for (int i = 0; i < s.size(); ++i) {
                if (s[i]) r.push_back(nums[i]);
            }
            res.insert(r);
        }

        vector<vector<int>> ans;
        for (auto c: res) {
            ans.push_back(c);
        }

        return ans;
    }
};
// @lc code=end

