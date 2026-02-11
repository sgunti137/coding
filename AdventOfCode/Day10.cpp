#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifndef ONLINE_JUDGE
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

int solve_easy(vector<string> grid) {
	int n = grid.size();
	int m = grid[0].size();

	int ans = 0;
	vector<pair<int, int>> z;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == '0') {
				z.push_back({i, j});
			}
		}
	}

	auto isInside = [&] (int a, int b) {
		if(a < 0 || b < 0 || a >= n || b >= m) {
			return false;
		}
		return true;
	};

	for(int id = 0; id < z.size(); ++id) {
		// do bfs for each zero

		int res = 0;
		vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		vector<vector<int>> vis(n, vector<int>(m, 0));

		queue<pair<int, int>> q;
		q.push({z[id].first, z[id].second}); 
	
		while(!q.empty()) {
			pair<int, int> node = q.front();
			q.pop();

			// use visited array for easy version
			// if(vis[node.first][node.second] == 1) continue;
			// vis[node.first][node.second] = 1;

			if(grid[node.first][node.second] == '9') {
				res++;
				continue;
			}

			for(auto d: dir) {
				int dx = node.first + d.first;
				int dy = node.second + d.second;

				if(isInside(dx, dy) && grid[dx][dy] == grid[node.first][node.second] + 1) {
					q.push({dx, dy});
				}
			}
		}

		debug() << imie(z[id]) imie(res);

		ans += res;
	}

	return ans;
}

int main() {
	vector<string> lines;

	int n; cin >> n;
	for(int i = 0; i < n; ++i) {
		string line;
		cin >> line;
		lines.push_back(line);
	}

	int ans = solve_easy(lines);

	cout << ans << endl;
}
