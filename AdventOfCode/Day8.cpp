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
	
	int n = grid.size(), m = grid[0].size();
	auto isInside = [&] (pair<int, int> x) {
		int a = x.first, b = x.second;
		if(a < 0 || b < 0 || a >= n || b >= m) {
			return 0;
		}
		return 1;
	};

	map<char, vector<pair<int, int>>> fq;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] != '.') {
				fq[grid[i][j]].push_back({i, j});
			}
		}
	}

	set<pair<int, int>> ans;

	for(auto x: fq) {
		vector<pair<int, int>> nodes = x.second;
		int sz = nodes.size();

		for(int i = 0; i < sz; ++i) {
			for(int j = i + 1; j < sz; ++j) {
				int dx = nodes[i].first - nodes[j].first;
				int dy = nodes[i].second - nodes[j].second;
				pair<int, int> p1 = {nodes[j].first - dx, nodes[j].second - dy};
				pair<int, int> p2 = {dx + nodes[i].first, dy + nodes[i].second};

				if(isInside(p1) && grid[p1.first][p1.second] != x.first) 
				{
					ans.insert(p1);
					grid[p1.first][p1.second] = '#';
				}
				if(isInside(p2) && grid[p2.first][p2.second] != x.first) {
					ans.insert(p2);
					grid[p2.first][p2.second] = '#';
				}
			}
		}
	}

	return ans.size();
}

// hard version just has a loop extra within instead of considering only 2 points
int solve_hard(vector<string> grid) {
	
	int n = grid.size(), m = grid[0].size();
	auto isInside = [&] (pair<int, int> x) {
		int a = x.first, b = x.second;
		if(a < 0 || b < 0 || a >= n || b >= m) {
			return 0;
		}
		return 1;
	};

	set<pair<int, int>> ans;

	map<char, vector<pair<int, int>>> fq;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] != '.') {
				fq[grid[i][j]].push_back({i, j});
				ans.insert({i, j});
			}
		}
	}

	for(auto x: fq) {
		vector<pair<int, int>> nodes = x.second;
		int sz = nodes.size();

		for(int i = 0; i < sz; ++i) {
			for(int j = i + 1; j < sz; ++j) {
				int dx = nodes[i].first - nodes[j].first;
				int dy = nodes[i].second - nodes[j].second;

				// Direction 1 -> from node j
				pair<int, int> p1 = {nodes[j].first - dx, nodes[j].second - dy};
				while(isInside(p1)) {
					if(grid[p1.first][p1.second] != x.first) {
						ans.insert(p1);
						grid[p1.first][p1.second] = '#';
					}

					p1 = {p1.first - dx, p1.second - dy};
				}
				
				// Direction 2 -> from node i
				pair<int, int> p2 = {dx + nodes[i].first, dy + nodes[i].second};
				while(isInside(p2)) {
					if(grid[p2.first][p2.second] != x.first) {
						ans.insert(p2);
						grid[p2.first][p2.second] = '#';	
					}

					p2 = {dx + p2.first, dy + p2.second};
				}
			}
		}
	}

	for(auto x: grid) {
		// debug() << imie(x);
	}

	return ans.size();
}

int main() {
	string line;
	vector<string> lines;

	ifstream file("in");

	while(getline(file, line)) {
		lines.push_back(line);
	}

	int ans = solve_easy(lines);
	ans = solve_hard(lines);

	cout << ans << endl;
}