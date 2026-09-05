#include <bits/stdc++.h>
#include <cassert>
#include <queue>
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
  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] > 0) {
      pq.push({a[i], i});
    }
  }

  if (pq.empty()) {
    string s(n, '1');
    cout << s << endl;
    return;
  }

  while (!pq.empty()) {
    priority_queue<pair<int, int>> new_pq;
    int sz = pq.size();
    while (!pq.empty()) {
      int val = pq.top().first;
      int id = pq.top().second;
      pq.pop();

      int r = 1, l = 1;
      // check right
      int m = 0, dm = 0;
      if (id + val >= n)
        r = 0;
      for (int t = id + 1; t <= id + val; ++t) {
        if (t >= n)
          break;
        if (a[t] == val + id - t) {
          m++;
        } else if (a[t] == -1) {
          continue;
        } else {
          dm++;
        }
      }

      if (dm)
        r = 0;
      else if (m > 1)
        r = 2;
      else if (m == 1 && id + val < n && a[id + val] == -1)
        r = 2;

      // check left
      m = 0, dm = 0;
      if (id - val < 0)
        l = 0;
      for (int t = id - 1; t >= id - val; --t) {
        if (t < 0)
          break;
        if (a[t] == val + t - id) {
          m++;
        } else if (a[t] == -1) {
          continue;
        } else {
          dm++;
        }
      }

      if (dm)
        l = 0;
      else if (m > 1)
        l = 2;
      else if (m == 1 && id - val >= 0 && a[id - val] == -1)
        l = 2;

      // cout << val << " " << id << endl;
      // cout << l << " " << r << endl;

      if (r == 2 || (r == 1 && l == 0)) {
        for (int t = id + 1; t <= id + val; ++t) {
          a[t] = val + id - t;
        }
      }
      if (l == 2 || (l == 1 && r == 0)) {
        for (int t = id - 1; t >= id - val; --t) {
          a[t] = val + t - id;
        }
      }

      if (l == 1 && r == 1) {
        new_pq.push({val, id});
      }

      if (l == 0 && r == 0) {
        cout << -1 << endl;
        return;
      }
    }

    if (sz == new_pq.size()) {
      while (!new_pq.empty()) {
        int val = new_pq.top().first;
        int id = new_pq.top().second;

        new_pq.pop();

        if (id + val < n) {
          for (int t = id + 1; t <= id + val; ++t) {
            a[t] = val + id - t;
          }
        }

        if (id - val >= 0) {
          for (int t = id - 1; t >= id - val; --t) {
            a[t] = val + t - id;
          }
        }
      }
    } else {
      pq = new_pq;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (a[i] > 0) {
      a[i] = 0;
    } else if (a[i] == 0) {
      a[i] = 1;
    } else
      a[i] = 0;
  }

  for (int i = 0; i < n; ++i) {
    cout << a[i];
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
