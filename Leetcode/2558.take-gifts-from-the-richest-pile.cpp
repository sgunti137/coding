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
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> pq;

        for (int i = 0; i < gifts.size(); ++i) {
            pq.push(gifts[i]);
        }

        for (int i = 0; i < k; ++i) {
            int top= pq.top();
            pq.pop();
            top = sqrt(top);

            pq.push(top);
        }
        
        long long int ans = 0;
        while (!pq.empty()) {
          ans += (long long int) pq.top();
          pq.pop();
        }

        return ans;
    }
};
// @leet end
