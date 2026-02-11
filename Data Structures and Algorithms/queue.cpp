#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node {
public:
	Node<T>* nextptr;
	T value;
	Node(const T& val) : value(val), nextptr(nullptr) {}
	Node() : value(0), nextptr(nullptr) {}
};

template <typename T>
class CustomQueue {
	int _sz = 0;
	Node<T>* _startPtr = nullptr;
	Node<T>* _endPtr = nullptr;

public:
	void push(const T& value) {
		Node<T>* newNode = new Node<T>(value);

		if (_sz == 0) {
			_startPtr = newNode;
			_endPtr = newNode;
		} else {
			_endPtr->nextptr = newNode;
			_endPtr = newNode;
		}

		_sz++;
	}

	void pop() {
		assert(_sz != 0);

		Node<T>* temp = _startPtr;
		_startPtr = _startPtr->nextptr;
		delete temp;

		_sz--;
	}

	T front() {
		return _startPtr->value;
	}

	T back() {
		return _endPtr->value;
	}

	bool empty() {
		return (_sz == 0);
	}

	int size() {
		return _sz;
	}
};