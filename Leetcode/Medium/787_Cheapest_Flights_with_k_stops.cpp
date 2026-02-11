#include <bits/stdc++.h>
using namespace std;

class SolutionDijkstra {

// dijkshtra algorithm.
// alternative: we can do bfs for k levels, whenever found the destination update the answer.
// alternative: we can do Bellman Ford Algorithm for upto k relaxations.

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int, int>> edges[n + 5];
        vector<vector<int>> vis(n + 5, vector<int>(k + 5, 0)), dis(n + 5, vector<int>(k + 5, INT_MAX));

        for(auto x: flights) {
            int from  = x[0];
            int to = x[1];
            int price = x[2];

            edges[from].push_back({to, price});
        }

        priority_queue<pair<int, pair<int, int>>> pq; // {-dist, node, k}
        dis[src][0] = 0;
        pq.push({0, {src, 0}});

        while(!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int node = top.second.first;
            int depth = top.second.second;

            if(vis[node][depth] == 1 || depth == k + 1) continue;

            vis[node][depth] = 1;
            for(auto x: edges[node]) {
                int new_dist = dis[node][depth] + x.second;

                if(new_dist < dis[x.first][depth + 1]) {
                    dis[x.first][depth + 1] = new_dist;
                    pq.push({-new_dist, {x.first, depth + 1}});
                }
            }
        }

        int ans = INT_MAX;

        for(int i = 0; i <= k + 1; ++i) {
            ans = min(ans, dis[dst][i]);
        }

        if(ans == INT_MAX) ans = -1;

        return ans;
    }
};

class SolutionBellmanFord {

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int, int>> edges[n + 5];
        vector<int> dist(n + 5, INT_MAX);
        dist[src] = 0;

        for(int i = 0; i <= k; ++i) {
            vector<int> new_dist = dist;
            for(auto x: flights) {
                int from  = x[0];
                int to = x[1];
                int price = x[2];

                if(dist[from] != INT_MAX && new_dist[to] > dist[from] + price) {
                    new_dist[to] = dist[from] + price;
                }
            }

            dist = new_dist;
        }

        if(dist[dst] == INT_MAX) {
            dist[dst] = -1;
        }

        return dist[dst];
    }
};