// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  vector<int> edges[100005], biedges[100005];

  void dfs(int node, vector<int> &vis) {
    vis[node] = 1;
    for (int x : edges[node]) {
      if (vis[x] == 1)
        continue;
      dfs(x, vis);
    }
  }

  void bidfs(int node, int par, vector<int> &bivis) {
    bivis[node] = 1;
    for (int x : biedges[node]) {
      if (x != par && bivis[x] != 1) {
        bidfs(x, node, bivis);
      }
    }
  }

  vector<int> remainingMethods(int n, int k, vector<vector<int>> &invocations) {
    for (int i = 0; i < n + 1; ++i) {
      edges[i].clear();
      biedges[i].clear();
    }
    for (int i = 0; i < invocations.size(); ++i) {
      edges[invocations[i][0]].push_back(invocations[i][1]);
      biedges[invocations[i][0]].push_back(invocations[i][1]);
      biedges[invocations[i][1]].push_back(invocations[i][0]);
    }

    vector<int> vis(n + 1, 0), bivis(n + 1, 0);
    dfs(k, vis);
    bidfs(k, -1, bivis);

    vector<int> ans;
    if (vis != bivis) {
      for (int i = 0; i < n; ++i) {
        ans.push_back(i);
      }
    } else {
      for (int i = 0; i < n; ++i) {
        if (vis[i] == 0)
          ans.push_back(i);
      }
    }

    return ans;
  }
};
// @leet end
/**/
