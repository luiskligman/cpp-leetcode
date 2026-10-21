#include <bits/stdc++.h>
using namespace std; 

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        array<int, 26> need{}, window{};
        int m = s1.size();

        // populate seen with the int representation of the char
        for (const char& c : s1) {
            need[c - 'a']++;
        }

        // use r in a for loop as it is monotonically increasing
        for (int r = 0; r < (int)s2.size(); ++r) {
            window[s2[r] - 'a']++;  // increment the count for the newly seen char

            // always remove the character from the left when the window is exceeding m
            if (r >= m) {
                window[s2[r - m] - 'a']--;
            }

            // if r is big enough to hold s1
            if (r >= m - 1 && window == need) {
                return true;
            }
            
        }

        return false;
    }


};