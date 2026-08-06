// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  int smallestNumber(int n, int t) {
    while (true) {
      int res = 1, x = n;

      while (x > 0) {
        res = res * (x % 10);
        x = x / 10;
      }

      if (res % t == 0)
        return n;
      n++;
    }
    return -1;
  }
};
// @leet end
