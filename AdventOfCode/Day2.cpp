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
		if(s[i] == ' ') {
			ans.push_back(stoi(res));
			res = "";
		} else {
			res.push_back(s[i]);
		}
	}
	if(res.size()) {
		ans.push_back(stoi(res));
	}

	return ans;
}

bool check(map<int, int> delta) {
	set<int> pos = {1, 2, 3}, neg = {-1, -2, -3};

	bool isPos = 1, isNeg = 1;
	for(auto x: delta) {
		if(pos.count(x.first) == 0 && x.second > 0) {
			isPos = 0;
		}

		if(neg.count(x.first) == 0 && x.second > 0) {
			isNeg = 0;
		}
	}

	if(isPos || isNeg) {
		return 1;
	}
	return 0;
}

int main() {
	string line;
	vector<string> lines;

	ifstream file("in");
	while(getline(file, line)) {
		lines.push_back(line);
	}
	file.close();

	int ans = 0;
	for(int i = 0; i < lines.size(); ++i) {
		string s = lines[i];
		vector<int> nums = parse(s);

		map<int, int> cur;
		for(int j = 1; j < nums.size(); ++j) {
			cur[nums[j] - nums[j - 1]]++;
		}

		// debug() << imie(cur);

		bool ok = 0;

		for(int skip = 0; skip < nums.size(); ++skip) {
			if(skip == 0) {
				cur[nums[1] - nums[0]]--;
			} else if(skip == nums.size() - 1) {
				cur[nums[nums.size() - 1] - nums[nums.size() - 2]]--;
			} else {
				cur[nums[skip] - nums[skip - 1]]--;
				cur[nums[skip + 1] - nums[skip]]--;
				cur[nums[skip + 1] - nums[skip - 1]]++;
			}

			// debug() << imie(skip) imie(cur);

			if(check(cur)) {
				ok = 1;
				break;
			}

			if(skip == 0) {
				cur[nums[1] - nums[0]]++;
			} else if(skip == nums.size() - 1) {
				cur[nums[nums.size() - 1] - nums[nums.size() - 2]]++;
			} else {
				cur[nums[skip] - nums[skip - 1]]++;
				cur[nums[skip + 1] - nums[skip]]++;
				cur[nums[skip + 1] - nums[skip - 1]]--;
			}
		}

		if(ok) ans++;

		// debug() << imie("  ");
	}
	cout << ans << endl;
}