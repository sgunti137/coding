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
  string smallestNumber(string num, long long t) {
    vector<int> p = {2, 3, 5, 7};
    vector<int> m(4, 0);

    for (int i = 0; i < 4; ++i) {
      while (t != 1 && t % p[i] == 0) {
        m[i]++;
        t /= p[i];
      }
    }

    if (t > 1) {
      return "-1";
    }

    for (int i = 0; i < num.size(); ++i) {
    }

    return "1";
  }
};
// @leet end
