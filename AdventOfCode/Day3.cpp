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

// easy version
vector<pair<int, int>> parse_easy(string s) {
	
	vector<pair<int, int>> ans;

	for(int i = 0; i < s.size(); ++i) {
		if(s.substr(i, 4) == "mul(") {
			int id = i + 7;
			int l = -1, r = -1;
			string res = "";
			for(int j = i + 4; j - i - 4 < 4; ++j) {
				if(s[j] == ',') {
					l = stoi(res);
					id = j;
				} else if(s[j] >= '0' && s[j] <= '9') {
					res.push_back(s[j]);
				} else {
					break;
				}
			}

			if(l == -1 || s[id] != ',') continue;
			// debug() << imie(l) imie(s[id]);

			res = "";
			for(int j = id + 1; j - id - 4 < 4; ++j) {
				if(s[j] == ')') {
					r = stoi(res);
					id = j;
				} else if(s[j] >= '0' && s[j] <= '9') {
					res.push_back(s[j]);
				} else {
					break;
				}
			}

			if(r == -1 || s[id] != ')') continue;
			// debug() << imie(l) imie(r);

			ans.push_back({l, r});
		}
	}

	return ans;
}

//NOTE: The do's and don'ts carry over from line to line. 
bool _do = 1;

// hard version
vector<pair<int, int>> parse_hard(string s) {
	vector<pair<int, int>> ans;

	for(int i = 0; i < s.size(); ++i) {

		if(s.substr(i, 4) == "do()") {
			_do = 1;
			continue;
		}

		if(s.substr(i, 7) == "don't()") {
			cout << 1 << endl;
			_do = 0;
			continue;
		}

		if(s.substr(i, 4) == "mul(") {
			int id = i + 7;
			int l = -1, r = -1;
			string res = "";
			for(int j = i + 4; j - i - 4 < 4; ++j) {
				if(s[j] == ',') {
					l = stoi(res);
					id = j;
				} else if(s[j] >= '0' && s[j] <= '9') {
					res.push_back(s[j]);
				} else {
					break;
				}
			}

			if(l == -1 || s[id] != ',') continue;
			// debug() << imie(l) imie(s[id]);

			res = "";
			for(int j = id + 1; j - id - 4 < 4; ++j) {
				if(s[j] == ')') {
					r = stoi(res);
					id = j;
				} else if(s[j] >= '0' && s[j] <= '9') {
					res.push_back(s[j]);
				} else {
					break;
				}
			}

			if(r == -1 || s[id] != ')') continue;
			// debug() << imie(l) imie(r) imie(_do);

			if(_do) ans.push_back({l, r});
		}
	}

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

	// easy version
	int ans = 0;
	for(int i = 0; i < lines.size(); ++i) {
		vector<pair<int, int>> res = parse_easy(lines[i]);
		for(auto x: res) {
			ans = ans + (x.first * x.second);
		}
	}

	// hard_version
	ans = 0;
	_do = 1;
	for(int i = 0; i < lines.size(); ++i) {
		vector<pair<int, int>> res = parse_hard(lines[i]);
		for(auto x: res) {
			ans = ans + (x.first * x.second);
		}
	}

	cout << ans << endl;
}