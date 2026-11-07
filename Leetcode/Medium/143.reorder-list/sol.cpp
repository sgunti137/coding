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

// 143. Reorder List
// https://leetcode.com/problems/reorder-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> in;

        ListNode* st = head;
        while (st != nullptr) {
            in.push_back(st);
            st = st -> next;
        }

        vector<ListNode*> first, last;
        for (int i = 0; i < in.size(); ++i) {
            if (i < (in.size() + 1) / 2) first.push_back(in[i]);
            else last.push_back(in[i]);
        }

        reverse(last.begin(), last.end());

        int f = 0, l = 0;
        bool ok = 0;
        ListNode* last_update = nullptr;
        while (true) {
            if (f == first.size() || l == last.size()) break;
            if (!ok) {
                first[f]->next = last[l];
                last_update = last[l];
                f++;
            } else {
                last[l]->next = first[f];
                last_update = first[f];
                l++;
            }
            ok = !ok;
        }

        if (last_update != nullptr) last_update->next  = nullptr;
    }
};
