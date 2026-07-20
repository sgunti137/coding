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

void test_case() {
  long long int n;
  cin >> n;
  vector<long long int> a(n);

  long long int extra = 0;
  for (long long int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] += extra;
    extra = max(0ll, a[i] - (i + 1));
    if (a[i] > i + 1) a[i] = i + 1;
  }

  // debug() << imie(a);

  bool ok = 1;
  for (long long int i = 0; i < n; ++i) {
    if (a[i] < (i + 1)) {
      ok = 0;
    }
  }

  cout << (ok ? "YES" : "NO") << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
	return 0;
}
