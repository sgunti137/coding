// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  int largestInteger(vector<int> &nums, int k) {
    int n = nums.size();

    if (n == k) {
      return *max_element(nums.begin(), nums.end());
    }

    unordered_map<int, int> mp;

    for (int i = 0; i < n; ++i) {
      mp[nums[i]]++;
    }

    if (k == 1) {
      int ma = -1;

      for (auto x : mp) {
        if (x.second == 1) {
          ma = max(ma, x.first);
        }
      }
      return ma;
    }

    if (nums[0] == nums.back()) {
      return -1;
    }

    if (mp[nums[0]] > 1)
      nums[0] = -1;
    if (mp[nums.back()] > 1)
      nums.back() = -1;
    return max(nums[0], nums.back());
  }
};
// @leet end
