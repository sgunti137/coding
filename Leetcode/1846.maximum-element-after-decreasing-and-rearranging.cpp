/*
 * @lc app=leetcode id=1846 lang=cpp
 *
 * [1846] Maximum Element After Decreasing and Rearranging
 */

#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& a) {
        int n = a.size();
        sort(a.begin(), a.end());

        a[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (abs(a[i] - a[i - 1]) <= 1) continue;
            a[i] = a[i - 1] + 1;
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, a[i]);
        }

        return ans;
    }
};
// @lc code=end

