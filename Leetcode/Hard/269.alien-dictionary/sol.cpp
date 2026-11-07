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

// 269. Alien Dictionary
// https://leetcode.com/problems/alien-dictionary/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        int n = words.size();
        unordered_set<char> a;
        for (int i = 0; i < words.size(); ++i) {
            for (auto c: words[i]) {
                a.insert(c);
            }
        }

        vector<char> ch;
        for (auto x: a) ch.push_back(x);

        map<char, int> in;
        map<char, vector<char>> edges;
        for (int i = 0; i < n - 1; ++i) {
            string s = words[i], t = words[i + 1];
            int p = 0;
            while (p < s.size() && p < t.size() && s[p] == t[p]) {
                p++;
            }
            if (p == s.size()) continue;
            if (p == t.size()) return ""; // corner case
            edges[s[p]].push_back(t[p]);
            in[t[p]]++;
        }

        queue<char> q;
        for (auto c: ch) {
            if (in[c] == 0) {
                q.push(c);
            }
        }

        string ans = "";
        while (!q.empty()) {
            char c = q.front();
            q.pop();

            ans += c;
            for (auto x: edges[c]) {
                in[x]--;
                if (in[x] == 0) {
                    q.push(x);
                }
            }
        }

        for (auto c: ch) {
            if (in[c]) {
                return "";
            }
        }

        return ans;
    }
};
