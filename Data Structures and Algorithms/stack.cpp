#include <bits/stdc++.h>
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