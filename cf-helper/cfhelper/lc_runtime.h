// Runtime for `lc run`: parses LeetCode-format input, calls Solution::method, prints the result.
#pragma once
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <iterator>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <type_traits>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace lc {

struct Reader {
    const string &s;
    size_t i = 0;
    explicit Reader(const string &str) : s(str) {}
    void ws() { while (i < s.size() && isspace((unsigned char)s[i])) i++; }
    char peek() { ws(); return i < s.size() ? s[i] : '\0'; }
    void expect(char c) {
        if (peek() != c) {
            cerr << "lc: parse error: expected '" << c << "' at position " << i << " in: " << s << "\n";
            exit(3);
        }
        i++;
    }
    bool accept(char c) { if (peek() == c) { i++; return true; } return false; }
    string token() {
        ws();
        size_t j = i;
        while (j < s.size() && s[j] != ',' && s[j] != ']' && !isspace((unsigned char)s[j])) j++;
        string t = s.substr(i, j - i);
        i = j;
        return t;
    }
};

template <class T> struct is_vector : false_type {};
template <class T, class A> struct is_vector<vector<T, A>> : true_type {};

inline void read(Reader &r, string &x) {
    r.expect('"');
    x.clear();
    while (r.i < r.s.size() && r.s[r.i] != '"') {
        if (r.s[r.i] == '\\' && r.i + 1 < r.s.size()) r.i++;
        x += r.s[r.i++];
    }
    r.expect('"');
}
inline void read(Reader &r, char &x) {
    if (r.accept('"')) { x = r.s[r.i++]; r.expect('"'); }
    else if (r.accept('\'')) { x = r.s[r.i++]; r.expect('\''); }
    else { r.ws(); x = r.s[r.i++]; }
}
inline void read(Reader &r, bool &x) { x = r.token() == "true"; }
inline void read(Reader &r, double &x) { x = stod(r.token()); }
inline void read(Reader &r, float &x) { x = stof(r.token()); }
template <class T>
typename enable_if<is_integral<T>::value>::type read(Reader &r, T &x) { x = (T)stoll(r.token()); }

template <class T> void read(Reader &r, vector<T> &v);

inline void read(Reader &r, ListNode *&head) {
    vector<int> v;
    read(r, v);
    ListNode dummy;
    ListNode *cur = &dummy;
    for (int x : v) cur = cur->next = new ListNode(x);
    head = dummy.next;
}

inline void read(Reader &r, TreeNode *&root) {
    vector<TreeNode *> nodes;
    r.expect('[');
    while (!r.accept(']')) {
        string t = r.token();
        nodes.push_back(t == "null" ? nullptr : new TreeNode(stoi(t)));
        r.accept(',');
    }
    root = nodes.empty() ? nullptr : nodes[0];
    size_t child = 1;
    for (size_t p = 0; p < nodes.size() && child < nodes.size(); p++) {
        if (!nodes[p]) continue;
        if (child < nodes.size()) nodes[p]->left = nodes[child++];
        if (child < nodes.size()) nodes[p]->right = nodes[child++];
    }
}

template <class T> void read(Reader &r, vector<T> &v) {
    v.clear();
    r.expect('[');
    while (!r.accept(']')) {
        T x{};
        read(r, x);
        v.push_back(x);
        r.accept(',');
    }
}

// ---- printing (LeetCode style, no spaces) ----
inline void print(ostream &o, const string &x) { o << '"' << x << '"'; }
inline void print(ostream &o, char x) { o << '"' << x << '"'; }
inline void print(ostream &o, bool x) { o << (x ? "true" : "false"); }
inline void print(ostream &o, double x) { char b[64]; snprintf(b, sizeof b, "%.5f", x); o << b; }
inline void print(ostream &o, float x) { print(o, (double)x); }
template <class T>
typename enable_if<is_integral<T>::value>::type print(ostream &o, T x) { o << (long long)x; }

template <class T> void print(ostream &o, const vector<T> &v);

inline void print(ostream &o, ListNode *h) {
    vector<int> v;
    for (; h; h = h->next) v.push_back(h->val);
    print(o, v);
}
inline void print(ostream &o, TreeNode *root) {
    vector<string> out;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *n = q.front(); q.pop();
        if (!n) { out.push_back("null"); continue; }
        out.push_back(to_string(n->val));
        q.push(n->left);
        q.push(n->right);
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    o << '[';
    for (size_t i = 0; i < out.size(); i++) o << (i ? "," : "") << out[i];
    o << ']';
}
template <class T> void print(ostream &o, const vector<T> &v) {
    o << '[';
    for (size_t i = 0; i < v.size(); i++) {
        if (i) o << ',';
        print(o, (const T &)v[i]);
    }
    o << ']';
}
// vector<bool> elements are proxies
inline void print(ostream &o, const vector<bool> &v) {
    o << '[';
    for (size_t i = 0; i < v.size(); i++) o << (i ? "," : "") << (v[i] ? "true" : "false");
    o << ']';
}

inline vector<string> input_lines() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        bool blank = line.find_first_not_of(" \t") == string::npos;
        if (!blank) lines.push_back(line);
    }
    return lines;
}

template <class Tuple, size_t... I>
void read_all(Tuple &t, const vector<string> &lines, index_sequence<I...>) {
    (void)initializer_list<int>{([&] {
        Reader r(lines[I]);
        read(r, get<I>(t));
    }(), 0)...};
}

template <class R, class C, class... A, class F>
void run_impl(F call) {
    vector<string> lines = input_lines();
    if (lines.size() < sizeof...(A)) {
        cerr << "lc: expected " << sizeof...(A) << " input lines, got " << lines.size() << "\n";
        exit(3);
    }
    tuple<typename decay<A>::type...> args;
    read_all(args, lines, index_sequence_for<A...>{});
    C obj;
    if constexpr (is_void<R>::value) {
        apply([&](auto &...a) { call(obj, a...); }, args);
        print(cout, get<0>(args));  // in-place problems: show the modified first argument
    } else {
        auto res = apply([&](auto &...a) { return call(obj, a...); }, args);
        print(cout, res);
    }
    cout << "\n";
}

template <class R, class C, class... A> void run(R (C::*f)(A...)) {
    run_impl<R, C, A...>([f](C &o, auto &...a) { return (o.*f)(a...); });
}
template <class R, class C, class... A> void run(R (C::*f)(A...) const) {
    run_impl<R, C, A...>([f](C &o, auto &...a) { return (o.*f)(a...); });
}

}  // namespace lc
