/*
 * @lc app=leetcode id=3499 lang=cpp
 *
 * [3499] Maximize Active Section with Trade I
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        vector<int> in;

        int cnt = 1, cur = s[0] - '0';
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i - 1]) {
                cnt++;
            } else {
                cur = 1 - cur;
                in.push_back(cnt);
                cnt = 1;
            }
        }
        in.push_back(cnt);

        // for (auto c: in) cout << c << " ";
        // cout << endl;

        int ans = 0, ma = 0;
        int id = 0;
        if (s[0] == '0') id++;

        for (int i = id; i < in.size(); i = i + 2) {
            ans += in[i];
            if (i + 4 < in.size()) ma = max(ma, in[i + 1] + in[i + 3]);
        }

        if (s[0] == '0' && in.size() > 2) ma = max(ma, in[0] + in[2]);
        if (s.back() == '0' && in.size() > 2) ma = max(ma, in.back() + in[in.size() - 3]);

        return ans + ma;
    }
};
// @lc code=end

/*

11 000 11 000 11
*/