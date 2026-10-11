#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> curr; // use curr as a stack

        function<void(int, int)> dfs = [&](int i, int total) {
            if (total == target) {
                res.push_back(curr);
                return;
            }

            if (i >= candidates.size() || total > target) {
                return;
            }

            // path where we include
            curr.push_back(candidates[i]);
            dfs(i, total + candidates[i]);

            // path where we dont include and restrict the use of the curr
            // element
            curr.pop_back();
            dfs(i + 1, total);
        };
    
        dfs(0, 0);
        return res;
    }
};