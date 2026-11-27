class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        // [1, 5, 0, 3, 5]
        // both 5s will reach 0 at the same time.
        // the 0 doesnt count
        // so there is only 3 unique values that will each require a separate
        // operation to decremement to 0 in this example

        unordered_set<int> seen;
        for (const int n : nums) {
            if (n != 0) {
                seen.insert(n);
            }
        }
        return seen.size();
    }
};
