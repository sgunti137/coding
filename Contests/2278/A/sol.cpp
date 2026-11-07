#include <bits/stdc++.h>
#include <iostream>
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

void test_case() {
	int n, m;
	cin >> n >> m;
	string p, q;
	cin >> p >> q;

	vector<int> ideal(26, 0);
	ideal['s' - 'a'] = 1;
	ideal['i' - 'a'] = 1;
	ideal['x' - 'a'] = 1;

	vector<int> is(26, 0);
	for (auto c: p) {
		is[c - 'a']++;
	}
	for (auto c: q) {
		is[c - 'a']--;
	}

	debug() << imie(is) imie(ideal);

	cout << (is == ideal ? "YES" : "NO") << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
	return 0;
}
