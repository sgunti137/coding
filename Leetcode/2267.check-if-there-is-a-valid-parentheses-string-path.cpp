// @leet imports start
// #include <bits/stdc++.h>
#include <unordered_set>
#include <vector>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
		int n = grid.size();
		int m = grid[0].size();

		vector<vector<unordered_set<int>>> g(n, vector<unordered_set<int>> (m));

		if (grid[0][0] == ')') return 0;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				int x = (grid[i][j] == '(' ? 1 : -1);
				if (i == 0 && j == 0) {
					g[i][j].insert(x);
				} else if (i == 0) {
					for (auto& y: g[i][j - 1]) {
						if (x + y < 0) continue;
						g[i][j].insert(x + y);
					}
				} else if (j == 0) {
					for (auto& y: g[i - 1][j]) {
						if (x + y < 0) continue;
						g[i][j].insert(x + y);
					}
				} else {
					for (auto& y: g[i][j - 1]) {
						if (x + y < 0) continue;
						g[i][j].insert(x + y);
					}
					for (auto& y: g[i - 1][j]) {
						if (x + y < 0) continue;
						g[i][j].insert(x + y);
					}
				}
			}
		}

		if (g[n - 1][m - 1].count(0)) {
			return 1;
		}
		return 0;
    }
};
// @leet end
