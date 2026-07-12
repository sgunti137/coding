/*
 * @lc app=leetcode id=1331 lang=cpp
 *
 * [1331] Rank Transform of an Array
 */
#include <bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        vector<pair<int, int>> in;

        for (int i = 0; i < n; ++i) {
            in.push_back({arr[i], i});
        }

        sort(in.begin(), in.end());

        int cur = 1;
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                arr[in[i].second] = cur;
                cur++;
            } else if (in[i].first == in[i - 1].first) {
                arr[in[i].second] = arr[in[i - 1].second];
            } else {
                arr[in[i].second] = cur;
                cur++;
            }
        }

        return arr;
    }
};
// @lc code=end

