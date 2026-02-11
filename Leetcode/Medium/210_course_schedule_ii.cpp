#include <bits/stdc++.h>
using namespace std;


/**
 * @class Solution
 * @brief Provides a solution to find the order of courses to finish all courses given the prerequisites.
 * @link https://leetcode.com/problems/course-schedule-ii/
 * 
 * This class contains a method to determine the order in which courses should be taken to satisfy all prerequisites.
 * 
 * @method findOrder
 * @param n The total number of courses.
 * @param prereq A vector of pairs where each pair [a, b] indicates that course a depends on course b.
 * @return A vector of integers representing the order of courses to be taken. If it is not possible to finish all courses, returns an empty vector.
 * 
 * The method uses Kahn's algorithm for topological sorting to determine the order of courses. It constructs a graph
 * using adjacency lists and computes the in-degrees of each node (course). It then uses a queue to process nodes with
 * zero in-degrees, updating the in-degrees of their neighbors and adding them to the queue if their in-degrees become zero.
 * If the resulting order contains all courses, it returns the order; otherwise, it returns an empty vector.
 */
class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& prereq) {
        vector<int> edges[n + 1];
        vector<int> indegree(n, 0);
        for(int i = 0; i < prereq.size(); ++i) {
            int a = prereq[i][0];
            int b = prereq[i][1];

            edges[b].push_back(a);
            indegree[a]++;
        }

        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> ans;

        while(!q.empty()) {
            int node = q.front();
            ans.push_back(node);
            q.pop();

            for(auto x: edges[node]) {
                indegree[x]--;
                if(indegree[x] == 0) {
                    q.push(x);
                }
            }
        }

        if(ans.size() == n) {
            return ans;
        }

        return {};
    }
};