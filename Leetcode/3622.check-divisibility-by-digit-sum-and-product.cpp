// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
  bool checkDivisibility(int n) {
    int sum = 0, p = 1;
    int t = n;
    while (t) {
      sum += t % 10;
      p *= (t % 10);
      t /= 10;
    }
    return (n % (sum + p) == 0 ? 1 : 0);
  }
};
// @leet end
