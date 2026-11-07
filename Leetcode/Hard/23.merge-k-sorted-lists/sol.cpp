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

// 23. Merge k Sorted Lists
// https://leetcode.com/problems/merge-k-sorted-lists/

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> nodes;
        ListNode head(0);
        ListNode* point = &head;
        for (ListNode* l : lists) {
            while (l) {
                nodes.push_back(l->val);
                l = l->next;
            }
        }
        sort(nodes.begin(), nodes.end());
        for (int x : nodes) {
            point->next = new ListNode(x);
            point = point->next;
        }
        return head.next;
    }
};
