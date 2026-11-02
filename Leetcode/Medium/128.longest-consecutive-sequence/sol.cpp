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

// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> mp;

		for (int i = 0; i < nums.size(); ++i) {
			mp.insert(nums[i]);
		}

		int ans = 0;
		for (auto& x: mp) {
			if (mp.count(x - 1) > 0) continue;
			int t = x, res = 0;
			while (mp.count(t) > 0) {
				t++;
				res++;
			}
			ans = max(ans, res);
		}

		return ans;
    }
};
