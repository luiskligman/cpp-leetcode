#include <bits/stdc++.h>
using namespace std;

// timing complexity: O(n + m)
// space complexity: O(n)
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> seen;
        vector<int> ret {};

        for (const int& n : nums1) {
            seen.insert(n);
        }

        for (const int& n : nums2) {
            if (seen.find(n) != seen.end()) { // n exists in the hash set
                ret.push_back(n);
                seen.erase(n);
            }
        }

        return ret;

    }
};