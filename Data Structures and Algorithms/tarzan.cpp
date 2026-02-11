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

const int mxN = 100005;
vector<int> edges[mxN];
int currentTime = 0;
vector<vector<int>> SCC;
vector<int> disc(mxN, -1), low(mxN, -1), inStack(mxN, -1);
stack<int> st;

void connect(int node, int par) {
	disc[node] = currentTime;
	low[node] = currentTime;
	currentTime++;

	st.push(node);
	inStack[node] = 1;

	for(auto v: edges[node]) {
		if(v == par) continue;
		if(disc[v] == -1) {
			connect(v, node);
			low[node] = min(low[node], low[v]);
		} else if(inStack[v] == 1) {
			low[node] = min(low[node], disc[v]);
		}
	}

	if(low[node] == disc[node]) {
		
		vector<int> res;

		while(true) {
			int v = st.top();
			inStack[v] = -1;
			st.pop();

			res.push_back(v);
			if(v == node) break;
		}
		
		SCC.push_back(res);
	}
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>> connections) {

	currentTime = 0;
	low.assign(n, -1);
	disc.assign(n, -1);
	inStack.assign(n, -1);
	while(st.size()) st.pop();
	SCC.clear();

	for(int i = 0; i < n; ++i) {
		edges[i].clear();
	}

	// create adjacency matrix
	for(auto x: connections) {
		edges[x[0]].push_back(x[1]);
		edges[x[1]].push_back(x[0]);
	}

	for(int i = 0; i < n; ++i) {
		if(disc[i] == -1) {
			connect(i, -1);
		}
	}

	vector<vector<int>> ans;

	for(int i = 0; i < connections.size(); ++i) {
		if(low[connections[i][0]] > disc[connections[i][1]] || disc[connections[i][0]] < low[connections[i][1]]) {
			ans.push_back(connections[i]);
		}
	}

	return ans;
}

void test_case() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> in;
	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		in.push_back({x, y});
	}

	vector<vector<int>> ans = criticalConnections(n, in);

	debug() << imie(ans);
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
}

