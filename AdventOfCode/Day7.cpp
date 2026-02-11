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

long long int pow(long long int a, long long int b) {
	if(b == 0) return 1;
	if(b == 1) return a;

	long long int res = a;
	
	res = pow(a, b / 2) * pow(a, b / 2);
	if(b % 2 == 1) res = res * a;
	
	return res;
}

long long int solve_easy(vector<string> lines) {
	auto parse = [&](string s) {
		long long int res = 0;
		vector<long long int> v;

		long long int x = 0;
		for(int i = 0; i < s.size(); ++i) {
			if(s[i] == ':') {
				res = x;
				x = 0;
				i++;
			} else if(s[i] == ' ') {
				v.push_back(x);
				x = 0;
			} else {
				x = (10 * x) + (s[i] - '0');
			}
		}

		v.push_back(x);

		return make_pair(res, v);
	};

	auto convertToBinary = [&](long long int a, int bits) {
		string s = "";
		while(a > 0) {
			if(a % 2 == 0) {
				s.push_back('0');
			} else {
				s.push_back('1');
			}
			a = a / 2;
		}
		while(bits > s.size()) {
			s.push_back('0');
		}
		reverse(s.begin(), s.end());
		return s;
	};
	
	vector<pair<long long int, vector<long long int>>> in;

	for(auto x: lines) {
		pair<long long int, vector<long long int>> res = parse(x);
		in.push_back(res);
	}

	long long int ans = 0;
	for(int i = 0; i < in.size(); ++i) {
		vector<long long int> v = in[i].second;
		long long int res = in[i].first;
		long long int mx = pow(2, v.size() - 1);

		vector<string> possibilities;

		for(long long int number = 0; number < mx; ++number) {
			string s = convertToBinary(number, v.size() - 1);
			possibilities.push_back(s);
		}

		bool ok = 0;
		for(auto pos: possibilities) {
			long long int result = v[0];
			for(int j = 1; j < v.size(); ++j) {
				if(pos[j - 1] == '0') {
					// addition
					result = result + v[j];
				} else {
					// multiplication
					result = result * v[j];
				}
			}
			if(result == res) {
				ok = 1;
			}
			// debug() << imie(pos) imie(result);
		}

		if(ok == 1) {
			ans = ans + res;
		}
	}

	return ans;	
}

long long int solve_hard(vector<string> lines) {
	auto parse = [&](string s) {
		long long int res = 0;
		vector<long long int> v;

		long long int x = 0;
		for(int i = 0; i < s.size(); ++i) {
			if(s[i] == ':') {
				res = x;
				x = 0;
				i++;
			} else if(s[i] == ' ') {
				v.push_back(x);
				x = 0;
			} else {
				x = (10 * x) + (s[i] - '0');
			}
		}

		v.push_back(x);

		return make_pair(res, v);
	};

	auto concat = [&](long long int a, long long int b) {

		vector<int> digits;
		while(b > 0) {
			digits.push_back(b % 10);
			b = b / 10;
		}
		reverse(digits.begin(), digits.end());

		for(int i = 0; i < digits.size(); ++i) {
			a = (10 * a) + digits[i];
		}
		return a;
	};

	vector<pair<long long int, vector<long long int>>> in;

	for(auto x: lines) {
		pair<long long int, vector<long long int>> res = parse(x);
		in.push_back(res);
	}

	long long int ans = 0;
	for(int i = 0; i < in.size(); ++i) {
		long long res = in[i].first;
		vector<long long int> v = in[i].second;

		set<long long int> s;
		s.insert(v[0]);
		for(int j = 1; j < v.size(); ++j) {
			set<long long int> a;
			for(auto x: s) {
				a.insert(concat(x, v[j]));
				a.insert(x + v[j]);
				a.insert(x * v[j]);
			}
			s = a;
		}

		if(s.count(res) != 0) {
			ans = ans + res;
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

	long long int ans = solve_easy(lines);
	ans = solve_hard(lines);

	cout << ans << endl;
}