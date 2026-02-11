#include <bits/stdc++.h>
using namespace std;

/**
 * @class Solution
 * @brief This class provides a solution to the Word Ladder problem.
 * 
 * The Word Ladder problem involves finding the shortest transformation sequence from a start word to an end word,
 * such that only one letter can be changed at a time and each transformed word must exist in a given word list.
 */
class Solution {
public:
    /**
     * @brief Compares two strings to determine if they differ by exactly one character.
     * 
     * @param a The first string to compare.
     * @param b The second string to compare.
     * @link https://leetcode.com/problems/word-ladder/
     * @return int Returns 1 if the strings differ by exactly one character, otherwise returns 0.
     */
    int compare(string a, string b);

    /**
     * @brief Finds the length of the shortest transformation sequence from beginWord to endWord.
     * 
     * @param beginWord The starting word.
     * @param endWord The target word.
     * @param wordList The list of allowed words for transformation.
     * @return int The length of the shortest transformation sequence, or 0 if no such sequence exists.
     */
    int ladderLength(string beginWord, string endWord, vector<string>& wordList);

    vector<int> edges[5005];

    int compare(string a, string b) {
        int cnt = 0;
        for(int i = 0; i < a.size(); ++i) {
            if(a[i] != b[i]) {
                cnt++;
            }
        }
        if(cnt == 1) return 1;
        return 0;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        vector<string> words;
        words.push_back(beginWord);
        bool ok = 0;
        for(auto x: wordList) {
            words.push_back(x);
            if(x == beginWord) {
                ok = 1;
            }
        }
        if(ok) {
            words = wordList;
        }
        int n = words.size();
        int start = 0, end = n;
        for(int i = 0; i < n; ++i) {
            if(words[i] == endWord) {
                end = i;
            } else if(words[i] == beginWord) {
                start = i;
            }
            for(int j = i + 1; j < n; ++j) {
                if(compare(words[i], words[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }

        vector<int> depth(n + 1, -1);
        depth[start] = 0;
        queue<int> q;
        q.push(start);
        while(q.size()) {
            int node = q.front();
            q.pop();
            for(auto i: edges[node]) {
                if(depth[i] == -1){
                    depth[i] = depth[node] + 1;
                    q.push(i);
                }
            }
            if(depth[end] != -1) break;
        }

        return depth[end]+1;
    }
};