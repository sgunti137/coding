/*
 * @lc app=leetcode id=3517 lang=cpp
 *
 * [3517] Smallest Palindromic Rearrangement I
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

