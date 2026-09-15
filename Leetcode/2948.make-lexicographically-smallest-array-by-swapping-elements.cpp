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
#include <unordered_map>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    int n = nums.size();
    vector<int> t = nums;
    sort(t.begin(), t.end());

    unordered_map<int, int> mp;
    int id = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (t[i + 1] - t[i] <= limit) {
        mp[t[i]] = id;
        mp[t[i + 1]] = id;
      } else {
        mp[t[i]] = id;
        mp[t[i + 1]] = id + 1;
        id++;
      }
    }

    // now i know which ids can be sorted, now sort them and place them back.
    vector<vector<int>> indexs(id + 1);
    vector<int> cur_ptr(id + 1, 0);

    for (int i = 0; i < n; ++i) {
      indexs[mp[nums[i]]].push_back(i);
    }

    for (int i = 0; i < n; ++i) {
      id = mp[t[i]];
      nums[indexs[id][cur_ptr[id]]] = t[i];
      cur_ptr[id]++;
    }

    return nums;
  }
};
// @leet end
