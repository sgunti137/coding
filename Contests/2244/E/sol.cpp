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

int find_lower(int x, vector<pair<int, int>> in) {
  int l = 0, r = in.size() - 1;
  int lmid = -1;

  while (l <= r) {
    int mid = l + (r - l) / 2;

    if (in[mid].first > x) {
      r = mid - 1;
      lmid = mid;
    } else if (in[mid].first == x) {
      return mid;
    } else {
      l = mid + 1;
    }
  }

  if (lmid == 0 || lmid == -1) {
    return 0;
  }

  if (in[lmid - 1].first <= x && in[lmid - 1].second >= x) {
    return lmid - 1;
  }

  return lmid;
}

int find_upper(int x, vector<pair<int, int>> in) {
  int l = 0, r = in.size() - 1;
  int lmid = -1;

  while (l <= r) {
    int mid = l + (r - l) / 2;

    if (in[mid].first > x) {
      r = mid - 1;
      lmid = mid;
    } else if (in[mid].first == x) {
      return mid;
    } else {
      l = mid + 1;
    }
  }

  if (lmid == 0) {
    return 0;
  }

  if (in[lmid - 1].first <= x && in[lmid - 1].second >= x) {
    return lmid - 1;
  }

  return lmid;
}

void test_case() {
  int n, q;
  string s;
  cin >> n >> q >> s;

  vector<pair<int, int>> zero, one;

  int st = -1;
  for (int i = 0; i < n; ++i) {
    if ((s[i] - '0') != i % 2) {
      if (st == -1) st = i;
    } else {
      if (st != -1) {
        zero.push_back({st, i - 1});
      }
      st = -1;
    }
  }

  if (st != -1) {
    zero.push_back({st, n - 1});
  }

  st = -1;
  for (int i = 0; i < n; ++i) {
    if ((s[i] - '0') == i % 2) {
      if (st == -1) st = i;
    } else {
      if (st != -1) {
        one.push_back({st, i - 1});
      }
      st = -1;
    }
  }

  if (st != -1) {
    one.push_back({st, n - 1});
  }

  debug() << imie(zero) imie(one);

  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;

    int zans = 0, oans = 0;

    int zl = find_lower(l, zero);
    int zr = find_lower(r, zero);

    int ol = find_lower(l, one);
    int or_ = find_lower(r, one);

    zans = zr - zl + 1;
    oans = or_ - ol + 1;

    cout << (k >= min(zans, oans) ? "YES" : "NO") << endl;
  }
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		test_case();
	}
	return 0;
}
