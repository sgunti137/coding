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

void function1() {
    cout << "Saaketh Gunti" << endl;
}

class cls {
    public:
    void operator()() {
        cout << "Output from f1" << endl;
    }

    void f2() {
        cout << "Output from f2" << endl;
    }
};

int main() {
    cls obj;
    thread t1(obj);

    cout << "Ouput from main" << endl;

    t1.join();
    return 0;
}