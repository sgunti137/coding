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

// 19. Remove Nth Node From End of List
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int sz = 0;
        ListNode* st = head;
        while (st != nullptr) {
            st = st->next;
            sz++;
        }

        cout << sz << " " << n << " ";

        if (sz == 1) return nullptr;
        else if (sz == n) return head -> next;

        ListNode* ptr = head;
        for (int i = 0; i < sz - n - 1; ++i) {
            ptr = ptr -> next;
        }

        cout << ptr -> val << endl;

        if (ptr -> next != nullptr && ptr -> next -> next != nullptr) ptr -> next = ptr -> next -> next;
        else if (ptr -> next != nullptr) ptr -> next = nullptr;

        return head;
    }
};
