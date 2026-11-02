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

// 261. Graph Valid Tree
// https://leetcode.com/problems/graph-valid-tree/

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        if (m != n - 1) return 0;

        vector<int> neighbors[n];
        for (auto x: edges) {
            neighbors[x[0]].push_back(x[1]);
            neighbors[x[1]].push_back(x[0]);
        }

        vector<bool> vis(n + 1, 0);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            vis[node] = 1;
            for (auto x: neighbors[node]) {
                if (vis[x]) continue;
                q.push(x);
            }
        }

        for (int i = 0; i < n; ++i) {
            if (!vis[i]) return 0;
        }

        return 1;
    }
};
