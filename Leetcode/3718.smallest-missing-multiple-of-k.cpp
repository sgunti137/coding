// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  int missingMultiple(vector<int> &nums, int k) {
    vector<int> e(105);

    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] % k || nums[i] / k > 100)
        continue;
      e[nums[i] / k] = 1;
    }

    for (int i = 1; i < e.size(); ++i) {
      if (!e[i])
        return i * k;
    }
    return 1;
  }
};
// @leet end
