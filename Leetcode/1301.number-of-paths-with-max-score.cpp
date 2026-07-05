/*
 * @lc app=leetcode id=1301 lang=cpp
 *
 * [1301] Number of Paths with Max Score
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
const int mod = 1e9 + 7;
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size(), m = board[0].size();

        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>> (m));

        dp[n - 1][m - 1] = {0, 1}; // {max score, number of ways}

        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (board[i][j] == 'X') {
                    dp[i][j] = {-1, -1};
                    continue;
                }

                if (i == n - 1 && j == m - 1) {
                    continue;
                }

                if (i == n - 1) {
                    if (dp[i][j + 1].first == -1) {
                        dp[i][j] = {-1, -1};
                        continue;
                    }
                    dp[i][j].first = (int)(board[i][j] - '0') + dp[i][j + 1].first;
                    dp[i][j].second = dp[i][j + 1].second;
                } else if (j == m - 1) {
                    if (dp[i + 1][j].first == -1) {
                        dp[i][j] = {-1, -1};
                        continue;
                    }
                    dp[i][j].first = (int)(board[i][j] - '0') + dp[i + 1][j].first;
                    dp[i][j].second = dp[i + 1][j].second;
                } else {
                    int up = dp[i][j + 1].first, left = dp[i + 1][j].first, diag = dp[i + 1][j + 1].first;

                    int mx = max({up, left, diag});
                    if (mx == -1) {
                        dp[i][j] = {-1, -1};
                        continue;
                    }
                    dp[i][j].first = (int)(board[i][j] - '0') + mx;
                    if (up == mx) {
                        dp[i][j].second += dp[i][j + 1].second % mod;
                        dp[i][j].second %= mod;
                    }
                    if (left == mx) {
                        dp[i][j].second += dp[i + 1][j].second % mod;
                        dp[i][j].second %= mod;
                    }
                    if (diag == mx) {
                        dp[i][j].second += dp[i + 1][j + 1].second % mod;
                        dp[i][j].second %= mod;
                    }
                }
            }
        }

        vector<int> ans(2);
        ans[0] = dp[0][0].first - board[0][0] + '0', ans[1] = dp[0][0].second;
        
        if (ans[1] == -1) {
            ans[0] = 0; ans[1] = 0;
        }

        return ans;
    }
};
// @lc code=end

