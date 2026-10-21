#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() < 1) {
            return 0;
        }

        unordered_set<char> seen;

        int length = 0;
        int l = 0;

        for (int r = 0; r < (int)s.size(); ++r) {
            while (seen.count(s[r])) {
                seen.erase(s[l]);
                l++;
            }
            seen.insert(s[r]);
            length = max(length, r - l + 1);
        }

        return length;
    }
};