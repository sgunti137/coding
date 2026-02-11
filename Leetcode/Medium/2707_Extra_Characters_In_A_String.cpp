// Link to the question: https://leetcode.com/problems/extra-characters-in-a-string/description/

#include <bits/stdc++.h>
using namespace std;

/* 
    This is top down DP approach
    Time complexity: O(n^3)
    Better solution is to use Trie data structure, which is O(n^2) in time complexicity
*/

class Solution {
public:
	/**
	 * @brief Computes the minimum number of extra characters needed to be removed to form the given string using words from the dictionary.
	 * 
	 * This function takes a string `s` and a vector of strings `dictionary`, and determines the minimum number of extra characters
	 * that need to be removed from `s` such that every substring of `s` is either a word in the dictionary
	 * 
	 * @param s The input string to be analyzed.
	 * @param dictionary A vector of strings representing the dictionary of words.
	 * @return int The minimum number of extra characters need to be removed.
	 */
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        int m = dictionary.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

		/* dp[i] indicates the best answer for the substring s[0..i-1]
		 * Now we have two options:
		 * 1. We can ignore the ith character and get the answer for the substring s[0 .. i+1] and add 1 to it.
		 * 2. Try to see if we can form a word from the dictionary by taking the substring s[i .. k] where k < n.
		*/

        set<string> dict;
        for(auto x: dictionary) {
            dict.insert(x);
        }
        for(int i = 0; i < n; ++i) {
			// option 1
            dp[i + 1] = min(dp[i + 1], 1 + dp[i]);
            
			// option 2
			for(int j = 0; j < m; ++j) {
                string x = dictionary[j];
                if(i + x.size() > n) continue;
                if(s.substr(i, x.size()) == x) {
                    dp[i + x.size()] = min(dp[i], dp[i + x.size()]);
                }
            }
        }
        return dp[n];
    }
};