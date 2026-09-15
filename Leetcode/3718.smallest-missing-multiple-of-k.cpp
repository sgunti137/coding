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
