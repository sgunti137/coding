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
  long long int n, m;
  cin >> n >> m;

  vector<long long int> a(n), b(m), pref(n);

  for (long long int i = 0; i < n; ++i) {
    cin >> a[i];
    pref[i] = a[i];
    if (i) pref[i] += pref[i - 1];
  }
  for (long long int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  sort(b.begin(), b.end());
  reverse(b.begin(), b.end());

  long long int cur = 1, ans = pref[n - 1];
  if (m) { ans -= pref[b[0] - 1]; }
  for (long long int i = 0; i < m; ++i) {
    long long int st = b[i] - 1;
    long long int val = pref[st];
    if (i < m - 1) val -= pref[b[i + 1] - 1];

    val = cur * val;

    if (val > 0) ans += val;
    else {
      ans -= val;
      cur = -1 * cur;
    }
  }

  cout << ans << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
	return 0;
}
