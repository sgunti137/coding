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

vector<int> parse(string s) {
	string res = "";
	vector<int> ans;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == ',') {
			ans.push_back(stoi(res));
			res = "";
		} else {
			res.push_back(s[i]);
		}
	}
	ans.push_back(stoi(res));
	return ans;
}


int main() {
	string line;
	vector<string> lines;

	ifstream file("in");
	while(getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	vector<int> edges[100], back[100], in(100, 0);

	int id = 0;
	for(id = 0; id < lines.size(); ++id) {
		if(lines[id] == "") {
			id++;
			break;
		}
		int l = stoi(lines[id].substr(0, 2));
		int r = stoi(lines[id].substr(3, 2));

		edges[l].push_back(r);
		back[r].push_back(l);
	}

	int ans = 0;

	for(int iid = id; iid < lines.size(); ++iid) {
		vector<int> order = parse(lines[iid]);
		if(order.size() == 1) {
			ans += order[0];
			continue;
		}

		bool ok = 1;

		vector<int> vis(100, 0);
		for(int i = 0; i < order.size(); ++i) {
			if(vis[order[i]] == 1) {
				ok = 0;
				break;
			}

			for(auto x: back[order[i]]) {
				vis[x] = 1;
			}

			vis[order[i]] = 1;
		}

		if(ok == 1) {
			continue;
		}

		for(int i = 0; i < order.size(); ++i) {
			for(int j = i + 1; j < order.size(); ++j) {
				bool ok = 1;
				for(auto x: back[order[i]]) {
					if(x == order[j]) {
						ok = 0;
					}
				}
				if(!ok) swap(order[i], order[j]);
			}
		}

		ans = ans + order[order.size() / 2];
	}

	cout << ans << endl;
}