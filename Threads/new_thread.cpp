#include <bits/stdc++.h>
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