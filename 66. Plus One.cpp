#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; i--) {

            if (digits[i] < 9) {
                digits[i]++;
                return digits; // no carry, done
            }
            digits[i] = 0; // was 9, becomes 0, carry continues
        }

        // extend vector by 1, incase all digits were 9s
        vector<int> result(digits.size() + 1, 0);
        result[0] = 1;

        return result;
    }
};