#include <bits/stdc++.h>
#include <cinttypes>
using namespace std;

// Binary Expo normal
int binPow(int a, int b) {
	if (a < 2) return a;
	
	int ans = 1;
	while (b > 0) {
		if ((b & 1) > 0) {
			ans = ans * a;
		}
		a = a * a;
		b = b >> 1;
	}

	return ans;
}

// Binary Expo mod
int binPow(int a, int b, int mod) {
	if (a < 2) return a;
	a = a % mod;

	int ans = 1;
	while (b) {
		if ((b & 1)) {
			ans = ans * a;
		}
		b >>= 1;
		a = a * a;
	}

	return ans;
}

int main() {
}
