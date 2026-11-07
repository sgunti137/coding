#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <climits>
#include <cmath>
using namespace std;

// 11. Container With Most Water
// https://leetcode.com/problems/container-with-most-water/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int l = 0, r = n - 1;

        int ans = 0;
        while (l < r) {
            int res = (r - l) * min(height[r], h`eight[l]);
            res = abs(res);
            ans = max(ans, res);

            if (height[l] > height[r]) {
                r--;
            } else if (height[r] > height[l]) {
                l++;
            } else {
                l++; r--;
            }
        }

        return ans;
    }
};
