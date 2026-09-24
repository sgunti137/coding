// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
		
		for (int i = 0; i < nums.size(); ++i) {
			int t = nums[i];
			int sum = 0;
			while (t > 0) {
				sum += t % 10;
				t /= 10;
			}

			if (sum == i) return i;
		}

		return -1;
    }
};
// @leet end
