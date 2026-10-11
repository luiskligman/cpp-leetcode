#include <bits/stdc++.h>
using namespace std;

// time complexity: O(n)
// space complexity: O(1)
class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        // you do not need to sort
        // just figure out how many are less than target
        // and how many equal target
        int less = 0;
        int equal = 0;
        for (const int& n : nums) {
            if (n < target) {
                less++;
            } else if (n == target) {
                equal++;
            }
        }

        vector<int> ret;
        for (int i = less; i < less + equal; i++) {
            ret.push_back(i);
        }

        return ret;
    }
};