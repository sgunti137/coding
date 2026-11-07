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

// 15. 3Sum
// https://leetcode.com/problems/3sum/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();

        map<int, vector<pair<int, int>>> mp;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                mp[nums[i] + nums[j]].push_back({i, j});
            }
        }

        set<vector<int>> res;
        for (int i = 0; i < n; ++i) {
            int t = -nums[i];

            vector<pair<int, int>> p = mp[t];
            for (auto c: p) {
                if (c.first != i && c.second != i) {
                    vector<int> v = {nums[i], nums[c.first], nums[c.second]};
                    sort(v.begin(), v.end());
                    res.insert(v);
                }
            }
        }

        vector<vector<int>> ans;
        for (auto x: res) {
            ans.push_back(x);
        }

        return ans;
    }
};
