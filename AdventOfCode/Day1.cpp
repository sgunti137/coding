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
		if(s[i] == ' ' && res != "") {
			ans.push_back(stoi(res));
			res = "";
		} else if(s[i] != ' ') {
			res.push_back(s[i]);
		}
	}
	if(res.size()) {
		ans.push_back(stoi(res));
	}

	assert(ans.size() == 2);

	return ans;
}

int main() {
	string line;
	vector<string> lines;

	ifstream file("in2");
	while(getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	vector<int> left, right;

	for(int i = 0; i < lines.size(); ++i) {
		string s = lines[i];
		vector<int> nums = parse(s);
		left.push_back(nums[0]);
		right.push_back(nums[1]);
	}

	// easy version
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	int ans = 0;
	for(int i = 0; i < left.size(); ++i) {
		ans += abs(left[i] - right[i]);
	}


	// hard version
	map<int, int> cnt;
	for(auto x: right) {
		cnt[x]++;
	}

	ans = 0;
	for(int i = 0; i < left.size(); ++i) {
		ans = ans + (left[i] * cnt[left[i]]);
	}

	cout << ans << endl;
}