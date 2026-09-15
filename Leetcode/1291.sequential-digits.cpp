/*
 * @lc app=leetcode id=1291 lang=cpp
 *
 * [1291] Sequential Digits
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <iterator>
#include <string>
#include <limits>
#include <complex>
#include <random>
#include <chrono>
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

