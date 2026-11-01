#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <climits>
#include <cmath>
using namespace std;

// 200. Number of Islands
// https://leetcode.com/problems/number-of-islands/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, 0));

        int ans = 0;
        vector<pair<int, int>> d = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j] == 1 || grid[i][j] == '0') continue;
                
                ans++;
                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = 1;

                while (!q.empty()) {
                    int x = q.front().first, y = q.front().second;
                    q.pop();
                    for (auto p: d) {
                        int dx = x + p.first, dy = y + p.second;
                        if (dx < 0 || dx > n - 1 || dy < 0 || dy > m - 1) continue;
                        if (vis[dx][dy] == 0 && grid[dx][dy] == '1') {
                            q.push({dx, dy});
                            vis[dx][dy] = 1;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
