// @leet imports start
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
		map<int, int> mp;

		for (auto& x: nums) mp[x] = 1;

		int ans = 0, res = 0, last = INT_MIN;
		for (auto& x: mp) {
			if (last == -1) {
				res = 1;
			} else if (last + 1 == x.first) {
				res++;
				ans = max(ans, res);
			} else {
				res = 1;
			}

			last = x.first;
			ans = max(ans, res);
		}

		return ans;
    }
};
// @leet end
