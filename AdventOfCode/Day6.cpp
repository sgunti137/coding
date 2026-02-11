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

#define ll long long

pair<int, bool> solve_easy(vector<string> grid) {
	int n = grid.size(), m = grid[0].size();
	int x, y;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == '^') {
				x = i;
				y = j;
			}
		}
	}

	vector<pair<int, int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int cur_dir = 0;

	auto isInside = [&](int x, int y) {
		if(x < 0 || y < 0 || x >= n || y >= m) {
			return 0;
		}
		return 1;
	};

	int cnt = 0;
	bool cycle = 0;
	while(true) {
		if(grid[x][y] == 'X') {
			cnt++;
		} else {
			cnt = 0;
		}

		// if(cool) debug() << imie(x) imie(y);

		grid[x][y] = 'X';
		x = x + dir[cur_dir].first;
		y = y + dir[cur_dir].second;

		if(isInside(x, y) == 0) {
			break;
		}

		if(cnt > 5 * n * m) {
			cycle = 1;
			break;
		}

		if(grid[x][y] == '#') {
			x = x - dir[cur_dir].first;
			y = y - dir[cur_dir].second;

			cur_dir = (cur_dir + 1) % 4;
			x = x + dir[cur_dir].first;
			y = y + dir[cur_dir].second;
		}
	}

	int ans = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == 'X') {
				ans++;
			}
		}
	}

	for(auto x: grid) {
		// debug() << imie(x);
	}
	
	return {ans, cycle};
}

// find 3,7,11 consequetive # and complete the cycle
// Gives wrong answer because there are some #'s in the grid which are not visited and they might affect the answer 
int solve_hard1(vector<string> grid) {
	int n = grid.size(), m = grid[0].size();

	int x, y;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == '^') {
				x = i;
				y = j;
			}
		}
	}

	vector<pair<int, int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int cur_dir = 0;

	auto isInside = [&](int x, int y) {
		if(x < 0 || y < 0 || x >= n || y >= m) {
			return 0;
		}
		return 1;
	};

	vector<pair<int, int>> order;
	vector<int> direction_order;

	int cnt = 0;
	while(cnt < n * m) {
		if(grid[x][y] == 'X') {
			cnt++;
		} else {
			cnt = 0;
		}

		grid[x][y] = 'X';
		x = x + dir[cur_dir].first;
		y = y + dir[cur_dir].second;

		if(isInside(x, y) == 0) {
			break;
		}

		if(grid[x][y] == '#') {
			order.push_back({x, y});
			direction_order.push_back(cur_dir);
			x = x - dir[cur_dir].first;
			y = y - dir[cur_dir].second;

			cur_dir = (cur_dir + 1) % 4;
			x = x + dir[cur_dir].first;
			y = y + dir[cur_dir].second;
		}
	}

	set<pair<int, int>> ans;

	int cycle_size = 4;
	while(cycle_size < order.size() + 1) {
		cur_dir = 3;
		for(int i = 0; i < order.size() - cycle_size + 2; ++i) {
			if(dir[cur_dir].first == 0) {
				x = order[i + cycle_size - 2].first + dir[(cur_dir + 1) % 4].first;
				y = order[i].second + dir[cur_dir].second;
			}
			if(dir[cur_dir].second == 0) {
				x = order[i].first + dir[cur_dir].first;
				y = order[i + cycle_size - 2].second + dir[(cur_dir + 1) % 4].second;
			}
			if(isInside(x, y)) {
				bool ok = 1;
				if(i + cycle_size - 1 < order.size()) {
					int dx = (x - order[i + cycle_size - 1].first) * dir[cur_dir].first;
					int dy = (y - order[i + cycle_size - 1].second) * dir[cur_dir].second;
					if(!(dx <= 0 && dy <= 0)) {
						ok = 0;
					}
				}
				if(ok) {
					grid[x][y] = 'O';
					ans.insert({x, y});
				}
			}
			cur_dir = (cur_dir + 1) % 4;
		}
		cycle_size += 4;
	}

	for(auto x: grid) {
		cout << x << endl;
	}

	return ans.size();
}

// Checks if the grid have a cycle, used in hard version
bool solveCycle(vector<string> grid, int x, int y, int cx, int cy) {

	int n = grid.size(), m = grid[0].size();

	vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
	int cur_dir = 0, repeat = 0;
	
	auto isInside = [&](int a, int b) {
		if(a < 0 || b < 0 || a >= n || b >= m) {
			return false;
		}
		return true;
	};

	while(true) {
		if(grid[x][y] == 'X') {
			repeat++;
		} else {
			repeat = 0;
		}

		grid[x][y] = 'X';

		x = x + dirs[cur_dir].first;
		y = y + dirs[cur_dir].second;

		if(!isInside(x, y)) {
			return false;
		}

		if(repeat >= 4 * n * m) {
			return true;
		}

		if(grid[x][y] == '#') {
			x = x - dirs[cur_dir].first;
			y = y - dirs[cur_dir].second;

			cur_dir = (cur_dir + 1) % 4;
		}
	}

	return 0;
}

// brute force, put a obstruction everywhere and check if it results in a cycle
int solve_hard(vector<string> grid) {
	int n = grid.size(), m = grid[0].size();

	pair<int, int> me;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == '^') {
				me = {i, j};
			}
		}
	}

	int ans = 0;
	vector<pair<int, int>> res;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(grid[i][j] == '#' || me == make_pair(i, j)) continue;
			grid[i][j] = '#';
			
			bool ok = solveCycle(grid, me.first, me.second, i, j);
			if(ok) {
				ans++;
				res.push_back({i, j});
			}

			grid[i][j] = '.';
		}
	}

	// debug() << imie(res);

	return ans;
}

int main() {
	string line;
	vector<string> lines;

	ifstream file("in");
	while(getline(file, line)) {
		lines.push_back(line);
	}

	int ans = solve_easy(lines).first;
	ans = solve_hard(lines);

	cout << ans << endl;
}