#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        /* XOR properties
         * x ^ x == 0
         * x ^ 0 == x */
        int init = 0;
        for (const auto& n : nums) {
            init ^= n;
        }
        return init;
    }
};