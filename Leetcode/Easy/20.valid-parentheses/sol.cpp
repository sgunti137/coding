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

// 20. Valid Parentheses
// https://leetcode.com/problems/valid-parentheses/

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                st.push(s[i]);
            } else if (s[i] == ')') {
                if (st.size() && st.top() == '(') st.pop();
                else return 0;
            } else if (s[i] == ']') {
                if (st.size() && st.top() == '[') st.pop();
                else return 0;
            } else if (s[i] == '}') {
                if (st.size() && st.top() == '{') st.pop();
                else return 0;
            } else {
                return 0;
            }
        }

        if (st.size()) return 0;
        return 1;
    }
};
