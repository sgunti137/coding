// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
		long long int l1 = (long long) rec1[2] - rec1[0];
		long long int b1 = (long long)rec1[3] - rec1[1];
		
		long long int l2 = (long long)rec2[2] - rec2[0];
		long long int b2 = (long long)rec2[3] - rec2[1];

		long long int l3 = (long long)max({rec1[0], rec1[2], rec2[0], rec2[2]}) - min({rec1[0], rec1[2], rec2[0], rec2[2]});
		long long int b3 = (long long)max({rec1[1], rec1[3], rec2[1], rec2[3]}) - min({rec1[1], rec1[3], rec2[1], rec2[3]});

		if (l3 < l1 + l2 && b3 < b1 + b2) return 1;
		return 0;
    }
};
// @leet end