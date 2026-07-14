/*
 * @lc app=leetcode id=1291 lang=cpp
 *
 * [1291] Sequential Digits
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<long long int> nums;
        vector<int> ans;
        for (int i = 1; i <= 9; ++i) {
            for (int st = 1; st <= 9; ++st) {
                long long int cur = st, d = 1, c = st + 1;
                bool ok = 1;
                while (d < i) {
                    cur = cur * 10;
                    if (c == 10) ok = 0;
                    cur += c;
                    c++;
                    d++;
                }
                if(ok) nums.push_back(cur);
            }
        }

        for (auto c: nums) {
            if (c >= low && c <= high) {
                ans.push_back(c);
            }
        }

        return ans;
    }
};
// @lc code=end

