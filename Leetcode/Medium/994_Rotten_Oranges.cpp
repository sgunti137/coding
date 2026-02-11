#include <bits/stdc++.h>
using namespace std;


/**
 * @class Solution
 * @brief Provides a solution to the problem of determining the minimum time required to rot all oranges in a grid.
 * @link https://leetcode.com/problems/rotting-oranges/
 * The class contains a single public method:
 * - int orangesRotting(vector<vector<int>>& grid): This method takes a 2D grid of integers where:
 *   - 0 represents an empty cell,
 *   - 1 represents a fresh orange,
 *   - 2 represents a rotten orange.
 * 
 * The method returns the minimum number of minutes that must elapse until no cell has a fresh orange. 
 * If this is impossible, the method returns -1.
 * 
 * The algorithm works as follows:
 * 1. Identify all initially rotten oranges and count the fresh oranges.
 * 2. Use a breadth-first search (BFS) approach to simulate the rotting process minute by minute.
 * 3. For each rotten orange, rot its adjacent fresh oranges and keep track of newly rotten oranges.
 * 4. Continue the process until no more fresh oranges can be rotted.
 * 5. If there are still fresh oranges left, return -1. Otherwise, return the number of minutes elapsed.
 * 
 * @param grid A 2D vector of integers representing the grid of oranges.
 * @return The minimum number of minutes required to rot all fresh oranges, or -1 if impossible.
 */
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        vector<pair<int, int>> rot;
        int ans = 0, cnt = 0; 
        int n = grid.size();
        int m = grid[0].size();
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(grid[i][j] == 2) {
                    rot.push_back({i, j});
                } else if(grid[i][j] == 1) {
                    cnt++;
                }
            }
        }

        while(!rot.empty()) {
            vector<pair<int, int>> new_rot;

            // add the newly rotten to new_rot
            for(int i = 0; i < rot.size(); ++i) {
                int x = rot[i].first, y = rot[i].second;
                if(x > 0 and grid[x - 1][y] == 1) {
                    grid[x - 1][y] = 2; cnt--;
                    new_rot.push_back({x - 1, y});
                }
                if(y > 0 and grid[x][y - 1] == 1) {
                    grid[x][y - 1] = 2; cnt--;
                    new_rot.push_back({x, y - 1});
                }
                if(y < m - 1 and grid[x][y + 1] == 1) {
                    grid[x][y + 1] = 2; cnt--;
                    new_rot.push_back({x, y + 1});
                }
                if(x < n - 1 and grid[x + 1][y] == 1) {
                    grid[x + 1][y] = 2; cnt--;
                    new_rot.push_back({x + 1, y});
                }
            }

            // increment the answer and update the rotten 
            if(new_rot.size()) {
                ans++;
            }
            rot = new_rot;
        }

        if(cnt != 0) {
            return -1;
        }
        return ans;
    }
};