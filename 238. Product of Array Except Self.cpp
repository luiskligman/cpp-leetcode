#include <bits/stdc++.h>
using namespace std;

// O(n) time complexity
// O(1) extra space
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {

        vector<int> out(nums.size(), 1);

        // forward pass
        int prefix = 1;
        for (int i = 0; i < nums.size(); i++) {
            out[i] = prefix;
            prefix *= nums[i];
        }

        // backward pass
        int postfix = 1;
        for (int i = nums.size() - 1; -1 < i; i--) {
            out[i] *= postfix;
            postfix *= nums[i];
        }

        return out;
    }
};