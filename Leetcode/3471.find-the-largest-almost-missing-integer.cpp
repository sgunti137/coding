// @leet imports start
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <iterator>
#include <string>
#include <limits>
#include <complex>
#include <random>
#include <chrono>
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
