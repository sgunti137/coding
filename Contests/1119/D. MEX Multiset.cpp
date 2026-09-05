#include <bits/stdc++.h>
using namespace std;
#define sim template <class c
#define ris return *this
#define dor > debug &operator<<
#define eni(x)                                                                 \
  sim > typename enable_if<sizeof dud<c>(0) x 1, debug &>::type operator<<(    \
            c i) {
sim > struct rge {
  c b, e;
};
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c *x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifndef ONLINE_JUDGE
  ~debug() { cerr << endl; }
  eni(!=) cerr << boolalpha << i;
  ris;
} eni(==) ris << range(begin(i), end(i));
}
sim, class b dor(pair<b, c> d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
  sim dor(const c &) { ris; }
#endif
}
;
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

void test_case() {
  int n;
  cin >> n;
  vector<int> a(n);
  map<int, int> cnt;
  int mx = INT_MIN;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    cnt[a[i]]++;
    mx = max(mx, a[i]);
  }

  if (cnt[0] == 1) {
    cout << "NO" << endl;
    return;
  }

  int id = -1;
  for (auto &x : cnt) {
    if (x.second < 3) {
      id = x.first;
      break;
    }
  }
  if (id == -1)
    id = mx;

  map<int, int> cov;
  string ans = "";
  for (int i = 0; i < n; ++i) {
    if (a[i] > id) {
      ans.push_back('C');
    } else {
      char c = char(cov[a[i]] % 3 + 'A');
      ans.push_back(c);
      cov[a[i]]++;
    }
  }

  cout << "YES" << endl;
  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    test_case();
  }
  return 0;
}
