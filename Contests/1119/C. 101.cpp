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
  int vis = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] == 1)
      vis = 1;
    if (a[i] == -1 && vis == 0) {
      a[i] = 1;
      vis = 1;
    }
  }
  vis = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (a[i] == 1)
      vis = 1;
    if (a[i] == -1 && vis == 0) {
      a[i] = 1;
      vis = 1;
    } else if (a[i] == -1) {
      a[i] = 0;
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    test_case();
  }
  return 0;
}
