/*
 * @lc app=leetcode id=3598 lang=cpp
 *
 * [3598] Longest Common Prefix Between Adjacent Strings After Removals
 */

#include <queue>
using namespace std;

// @lc code=start
class Solution {
public:

    int pref_val (string a, string b) {
        int res = 0;
        for (int j = 0; j < min(a.size(), b.size()); ++j) {
            if (a[j] != b[j]) {
                break;
            }
            res++;
        }
        return res;
    }

    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        vector<int> ans(n, 0);
        vector<int> pref(n - 1);
        priority_queue<int> pq;
        for (int i = 0; i < n - 1; ++i) {
            int res = pref_val(words[i], words[i + 1]);
            pref[i] = res;
            pq.push(res);
            if (i) ans[0] = max(ans[0], res);
            if (i < n - 2) ans[n - 1] = max(ans[n - 1], res);
        }

        for (int i = 1; i < n - 1; ++i) {
            vector<int> val(2, -1);

            val[0] = pref[i - 1];
            val[1] = pref[i];

            if (val[0] < val[1]) swap(val[0], val[1]);

            if (val[0] == pq.top()) {
                pq.pop();
                if (val[1] == pq.top()) {
                    pq.pop();
                    ans[i] = max(pq.top(), pref_val(words[i - 1], words[i + 1]));
                    pq.push(val[1]);
                } else {
                    ans[i] = max(pq.top(), pref_val(words[i - 1], words[i + 1]));
                }
                pq.push(val[0]);
            } else {
                ans[i] = max(pq.top(), pref_val(words[i - 1], words[i + 1]));
            }
        }

        return ans;
    }
};


/*

Thoughts: 
1. Remove each one and calculate [Brute force]
    Store the result for every 2 adjacent; if i got removed, remove the pairs (i-1, i) and (i, i+1) get the max of all rem and (i-1, i+1)
        This also needs to get the max element. So the idea is N^2
    We need something with Nlog(N)

    Can i do above using heap?
    Construct the heap with the initial data; now for each i, check if the 2 impacted are at the top? 
        if they are at the top 2 remove them and check the max of new top and the i-1, i+1 pair
    If they are not at the top, then check the max of i-1, i+1 and heap.top

    Do i really need heap?
    No, only the top 3 elements is required! It can still be optimised

2. If the max is created due to (t, t+1); only if one of them is removed the max changes!
    This is wrong as (run, jump, run) if jump is removed, answer increases

*/

// @lc code=end
