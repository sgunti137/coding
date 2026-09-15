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
#include <climits>
using namespace std;
// @leet imports end

// @leet start
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
  vector<int> nodesBetweenCriticalPoints(ListNode *head) {
    vector<int> ids, a(3, -1);

    int id = 0, ma = INT_MIN, mi = INT_MAX;
    while (head != nullptr) {
      int val = head->val;
      a[0] = a[1];
      a[1] = a[2];
      a[2] = val;
      if (a[0] != -1 && (a[1] > a[0] && a[1] > val) ||
          (a[1] < a[0] && a[1] < val)) {
        ids.push_back(id);
        if (ids.size() > 1)
          ma = max(ma, ids.back() - ids[0]);
        if (ids.size() > 1)
          mi = min(mi, ids.back() - ids[ids.size() - 2]);
      }
      id++;
      head = head->next;
    }

    if (ma == INT_MIN)
      return {-1, -1};
    return {mi, ma};
  }
};
// @leet end
