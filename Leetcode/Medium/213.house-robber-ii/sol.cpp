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

// 213. House Robber II
// https://leetcode.com/problems/house-robber-ii/

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return nums[0];
        vector<int> dp(n + 1, 0);

        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            dp[i] = nums[i];
            int res = 0;
            if (i > 1) res = dp[i - 2];
            if (i > 2) res = max(res, dp[i - 3]);
            dp[i] += res;
            ans = max(ans, dp[i]); 
        }

        for(auto& x: dp) x = 0;
        for (int i = 1; i < n; ++i) {
            dp[i] = nums[i];
            int res = 0;
            if (i > 1) res = dp[i - 2];
            if (i > 2) res = max(res, dp[i - 3]);
            dp[i] += res;
            ans = max(ans, dp[i]); 
        }

        return ans;
    }
};
