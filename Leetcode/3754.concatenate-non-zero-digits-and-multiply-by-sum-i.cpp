/*
 * @lc app=leetcode id=3754 lang=cpp
 *
 * [3754] Concatenate Non-Zero Digits and Multiply by Sum I
 */

// @lc code=start
class Solution {
public:
    long long sumAndMultiply(int n) {
        int x = 0, sum = 0;
        int p = 1;

        while (n > 0) {
            int t = n % 10;
            if (t) {
                sum += t;
                x += (p * t);
                p *= 10;
            }
            n /= 10;
        }

        return (long long) x * sum;
    }
};
// @lc code=end

