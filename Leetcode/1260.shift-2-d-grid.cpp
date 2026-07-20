/*
 * @lc app=leetcode id=1260 lang=cpp
 *
 * [1260] Shift 2D Grid
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans = grid;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int eff = (i * m + j + k) % (m * n);
                int ni = eff / m;
                int nj = eff % m;
                ans[ni][nj] = grid[i][j];
            }
        }

        return ans;
    }
};
// @lc code=end

