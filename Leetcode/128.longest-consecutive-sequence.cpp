// @leet imports start
#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
// @leet imports end

// @leet start
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
// @leet end
