// @leet imports start
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  vector<int> findMissingElements(vector<int> &nums) {
    int ma = INT_MIN, mi = INT_MAX;
    vector<int> vis(105);
    for (int i = 0; i < nums.size(); ++i) {
      ma = max(ma, nums[i]);
      mi = min(mi, nums[i]);
      vis[nums[i]] = 1;
    }

    vector<int> ans;
    for (int i = mi; i <= ma; ++i) {
      if (vis[i] == 0) {
        ans.push_back(i);
      }
    }

    return ans;
  }
};
// @leet end
