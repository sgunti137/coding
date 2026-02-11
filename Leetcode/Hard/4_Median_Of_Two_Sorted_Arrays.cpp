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

/**
 * @file 4_Median_Of_Two_Sorted_Arrays.cpp
 * @brief This file contains the implementation of the Solution class which provides a method to find the median of two sorted arrays.
 * 
 * The main function of interest is `findMedianSortedArrays` which takes two sorted vectors of integers and returns the median of the combined sorted array.
 * 
 * The algorithm uses binary search to efficiently find the median, ensuring a time complexity of O(log(min(n, m))), where n and m are the sizes of the input arrays.
 * 
 * The inputs are modified to include INT_MIN and INT_MAX at the start and end respectively to handle edge cases.
 * 
 * @class Solution
 * @method double findMedianSortedArrays(vector<int> a, vector<int> b)
 * @param a The first sorted vector of integers.
 * @param b The second sorted vector of integers.
 * @return The median of the two sorted arrays as a double.
 * 
 * The method handles the following cases:
 * - If one of the arrays is empty, it directly computes the median from the non-empty array.
 * - It ensures that the smaller array is used for binary search to optimize time complexity.
 * - It checks conditions to find the correct partition where the median lies.
 * - If the combined length of the arrays is even, it returns the average of the two middle elements.
 * - If the combined length is odd, it returns the middle element.
 * 
 * The main function reads the sizes of the two arrays and initializes them with INT_MIN and INT_MAX.
 */

class Solution {
	public:
		double findMedianSortedArrays(vector<int> a, vector<int> b) {
			// the inputs have added INT_MIN & INT_MAX at the start and end respectively to consider the corner cases of taking all or nothing in each array
			int n = a.size() - 2, m = b.size() - 2;
			int leftContains = (n + m + 1) / 2;

			// interchange based on size of the vector, take the minimum for better time complexicity
			if(n > m) {
				swap(n, m);
				swap(a, b);
			}

			// if there are no elements in an array, just use the second array to calculate the answer
			if(n == 0) {
				if(m % 2 == 0) {
					double res = double(b[m / 2] + b[m / 2 + 1]) / 2.0;
					return res;
				} else {
					return (double) b[(m + 1) / 2];
				}
			}

			int left = 0, right = n + 1;
			while(left <= right) {
				int mid = left + (right - left) / 2;
				int bl = leftContains - mid; // calculate the element in b which will be in the left part after the merge of both arrays
				
				// conditions for mid being the median
				bool up = a[mid] <= b[bl + 1];
				bool down = a[mid + 1] >= b[bl];

				// debug() << imie(left) imie(right) imie(mid);
				// debug() << imie(a[mid]) imie(b[bl]) imie(up) imie(down);

				if(up && down) {
					// conditions are met
					if((n + m) % 2  == 0) {
						int ll = max(a[mid], b[bl]);
						int rr = min(a[mid + 1], b[bl + 1]);
						return double(ll + rr) / 2.0;
					} else {
						double res = 1.0 * (double) max(a[mid], b[bl]);
						return res;
					}
				}

				if(!up) {
					right = mid - 1;
				} else if(!down) {
					left = mid + 1;
				} else {
					return (double) -1.0;
				}
				
				// debug() << imie("");
			}
			return -1.0;
		}
	};

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 2, INT_MIN), b(m + 2, INT_MIN);
	for(int i = 0; i < n; ++i) {
		cin >> a[i + 1];
	}
	for(int j = 0; j < m; ++j) {
		cin >> b[j + 1];
	} 
	a[n + 1] = INT_MAX; b[m + 1] = INT_MAX;

	debug() << imie(a) imie(b);
	Solution ans;
	cout << ans.findMedianSortedArrays(a, b) << endl;
}

/*

4 5
1 2 5 6
3 4 7 8 9
left contains 5, right contains 4

i 0, j 3, mid = 1 -> compare 7 < 5 && 2 < 8 -> mid moves right
i 2, j 3, mid = 2 -> compare 4 < 6 && 5 < 7 => condition satisfied => median larger value of 5 and 4 => 5

5 5
1 2 3 8 9
4 5 6 7 10
left contains 5, right contains 5

i = 0, j = 5, mid = 2 -> compare 6 < 3 && 2 < 7 -> mid moves right
i = 3, j = 5, mid = 4 -> compare 5 < 9 && 8 < 5 -> mid moves left
i = 3, j = 3, mid = 3 -> compare 5 < 8 && 3 < 6 -> condition satisfied => median value = max(left) + min(right) / 2

*/