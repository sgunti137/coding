// @leet imports start
#include <bits/stdc++.h>
using namespace std;
// @leet imports end

// @leet start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
		if (node == nullptr) return nullptr;

        unordered_map<Node*, Node*> cloned;
        queue<Node*> q;

        cloned[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();

            for (Node* neighbor : cur->neighbors) {
                if (!cloned.count(neighbor)) {
                    cloned[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                cloned[cur]->neighbors.push_back(cloned[neighbor]);
            }
        }

        return cloned[node];
	}
};
// @leet end
