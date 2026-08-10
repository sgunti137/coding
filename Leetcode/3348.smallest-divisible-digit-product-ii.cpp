// @leet imports start
#include <bits/stdc++.h>
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
