/*
 * @lc app=leetcode id=3517 lang=cpp
 *
 * [3517] Smallest Palindromic Rearrangement I
 */
#include <bits/stdc++.h>
using namespace std;

// @lc code=start
class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.size();

        map<char, int> mp;
        for (int i = 0; i < n; ++i) {
            mp[s[i]]++;
        }

        int id = 0;
        for (auto x: mp) {
            char c = x.first;
            int val = x.second;

            for (int i = 0; i < val / 2; ++i) {
                s[id + i] = c;
                s[n - 1 - id - i] = c;
            }

            if (val == 1) {
                s[id] = c;
            }

            id = val / 2 + id;
        }

        return s;
    }
};
// @lc code=end

