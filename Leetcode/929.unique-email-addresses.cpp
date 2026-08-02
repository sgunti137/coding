/*
 * @lc app=leetcode id=929 lang=cpp
 *
 * [929] Unique Email Addresses
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> s;

        for (int i = 0; i < emails.size(); ++i) {
            string name = "", domain = "";
            bool ok = 0;

            for (int j = 0; j < emails[i].size(); ++j) {
                if (ok) {
                    domain += emails[i][j];
                } else if (emails[i][j] == '@') {
                    ok = 1;
                } else if (emails[i][j] == '.') {
                    continue;
                } else if (emails[i][j] == '+') {
                    while (emails[i][j] != '@') {
                        j++;
                    }
                    j--;
                } else {
                    name += emails[i][j];
                }
            }
            string res = name + "@" + domain;
            s.insert(res);
        }

        return s.size();
    }
};
// @lc code=end

