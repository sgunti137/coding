/*
 * @lc app=leetcode id=3016 lang=cpp
 *
 * [3016] Minimum Number of Pushes to Type Word II
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
    int minimumPushes(string word) {
        int n = word.size();
        vector<int> cnt(26);
        for (int i = 0; i < n; ++i) {
            cnt[word[i] - 'a']++;
        }
        sort(cnt.begin(), cnt.end());
        reverse(cnt.begin(), cnt.end());

        int cur_num_id = 1, num = 1;

        int ans = 0;
        for (int i = 0; i < 26; ++i) {

            if (cnt[i] == 0) break;

            ans += (cur_num_id * cnt[i]);
            num++;

            if (num == 9) {
                num = 1;
                cur_num_id++;
            }
        }
        return ans;
    }
};
// @lc code=end

