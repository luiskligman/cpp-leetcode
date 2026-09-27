#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int ret = 0;
        sort(nums.begin(), nums.end());

        for (int i = nums.size() - 1; i >= 0; i -= 2) {
            ret += min(nums[i], nums[i - 1]);
        }

        return ret;
    }
};
