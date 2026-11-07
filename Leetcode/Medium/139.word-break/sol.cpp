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

// 139. Word Break
// https://leetcode.com/problems/word-break/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> ans(n + 1, 0);

        ans[0] = 1;
        for (int i = 0; i < n; ++i) {
            if (ans[i] == 1) {
                for (auto x: wordDict) {
                    if (s.substr(i, x.size()) == x) {
                        ans[i + x.size()] = 1;
                    }
                }
            }
        }

        return ans[n];
    }
};
