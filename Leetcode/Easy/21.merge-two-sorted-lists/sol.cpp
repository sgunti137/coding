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

// 21. Merge Two Sorted Lists
// https://leetcode.com/problems/merge-two-sorted-lists/

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;

        while (list1 != nullptr || list2 != nullptr) {
            bool ok = 0;
            if (list1 == nullptr) {
                ok = 1;
            } else if (list2 == nullptr) {
                ok = 0;
            } else if (list1 -> val > list2 -> val) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok) {
                cur -> next = list2;
                list2 = list2 -> next;
                cur = cur -> next;
            } else {
                cur -> next = list1;
                list1 = list1 -> next;
                cur = cur -> next;
            }
        }

        return dummy->next;
    }
};
