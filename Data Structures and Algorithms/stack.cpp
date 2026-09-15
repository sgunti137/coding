#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <ctime>
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
#include <complex>
#include <random>
#include <chrono>
using namespace std;

template <typename T> class CustomStack {
    // Public Variables: None
    // Private variables: array
    vector<T> array;

public:
    // Constructor
    CustomStack() {}

    void push(T value) { array.push_back(value); }

    void pop() { array.pop_back(); }

    T top() { return array.back(); }

    void clear() { array.clear(); }

    bool empty() { return (array.size() == 0); }

    int size() { return array.size(); }
};