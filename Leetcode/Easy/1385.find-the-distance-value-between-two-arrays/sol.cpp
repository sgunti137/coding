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

// 1385. Find the Distance Value Between Two Arrays
// https://leetcode.com/problems/find-the-distance-value-between-two-arrays/

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int ans = 0;
		for (int i = 0; i < arr1.size(); ++i) {
			bool ok = 0;
			for (int j = 0; j < arr2.size(); ++j) {
				if (abs(arr1[i] - arr2[j]) <= d) ok = 1;
			}
			if (ok == 0) ans++;
		}
		return ans;
    }
};
