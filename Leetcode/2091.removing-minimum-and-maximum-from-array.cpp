// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  int minimumDeletions(vector<int> &nums) {
    int n = nums.size();

    int mi = INT_MAX, ma = INT_MIN;
    int a = -1, b = -1;
    for (int i = 0; i < n; ++i) {
      if (nums[i] > ma) {
        ma = nums[i];
        a = i;
      }
      if (nums[i] < mi) {
        mi = nums[i];
        b = i;
      }
    }

    if (a > b)
      swap(a, b);

    return min({b + 1, n - a, a + n - b + 1});
  }
};
// @leet end
