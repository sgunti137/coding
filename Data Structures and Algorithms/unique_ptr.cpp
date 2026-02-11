#include <bits/stdc++.h>
using namespace std;

template <class T>
class unique_ptr {
    private:
        T* _ptr;

    public:
        // default constructor
        unique_ptr(): _ptr(nullptr) {
        }

        // parameterized constructor
        unique_ptr(T ptr = nullptr): _ptr(*ptr) {
        }

        // copy constructor
        unique_ptr(unique_ptr& unq) = delete;

        // destructor
        ~unique_ptr() {
            delete _ptr;
        }

        void reset() {
            T* oldptr = release(_ptr);
            _ptr = nullptr;
            if(oldptr != nullptr) {
                delete oldptr;
            }
        }

        T* release() {
            T* newptr = _ptr;
            _ptr = nullptr;
            return newptr;
        }
};