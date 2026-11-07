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

// 152. Maximum Product Subarray
// https://leetcode.com/problems/maximum-product-subarray/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        long long int pos_min = INT_MAX, neg_max = INT_MIN;
        long long int cur = 1, ans = nums[0];

        for (int i = 0; i < n; ++i) {
            cur = cur * nums[i];
            ans = max(ans, cur);

            if (cur > 0) {
                if (pos_min != INT_MAX) ans = max(ans, cur / pos_min);
            } else if (cur < 0) {
                if (neg_max != INT_MIN) ans = max(ans, cur / neg_max);
            }

            cerr << cur << " " << pos_min << " " << neg_max << " " << ans << endl;

            if (cur > 0) {
                pos_min = min(cur, pos_min);
            } else if (cur < 0) {
                neg_max = max(cur, neg_max);
            } else {
                cur = 1;
                pos_min = INT_MAX;
                neg_max = INT_MIN;
            }
        }

        return (int) ans;
    }
};
