#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {

        vector<vector<int>> ret;
        vector<int> curr;  // curr acts like a stack, LIFO

        // must use function<void(int)> for a recursive lambda
        function<void(int)> dfs = [&](const int& i) {
            if (i == nums.size()) {
                ret.push_back(curr);
                return;
            }

            curr.push_back(nums[i]); // include nums[i]
            dfs(i + 1);
            curr.pop_back();

            dfs(i + 1); // exclude nums[i]
        };

        dfs(0);

        return ret;
    }
};