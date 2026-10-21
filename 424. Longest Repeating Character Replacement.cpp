#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int length = 0;

        int l = 0;

        unordered_map<char, int> count;

        for (int r = 0; r < s.length(); ++r) {
            count[s[r]]++;  // always add new char
            while ((r - l + 1) - getMax(count) > k) {  // shrink while window is invalid
                count[s[l]]--;
                l++;
            }
            
            length = max(length, r - l + 1);  // window is now valid, record its length
        }
        return length;

    }

    // getMax() returns the count of the char that occurs the most in the current window
    int getMax(const unordered_map<char, int>& count) {
        int ret = 0;
        for (const auto& [k, v] : count) {
            ret = max(ret, v);
        }
        return ret;
    }
};