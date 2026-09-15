// @leet imports start
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
