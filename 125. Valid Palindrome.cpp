#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string clean{""};

        // clean string of uppercase / spaces
        for (const auto& c : s) {
            if (isalnum(c)) {
                clean += tolower(c);
            }
        }

        // two pointers
        int i = 0;
        int j = clean.size() - 1;

        while (i < j) {
            if (clean[i] != clean[j]) {
                return false;
            }
            i++;
            j--;
        }

        return true;
    }
};