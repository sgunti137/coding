// @leet imports start
#include <bits/stdc++.h>
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
