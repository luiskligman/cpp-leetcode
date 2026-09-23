#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int longest = 0;
        unordered_set<int> seen;

        for (const auto& n : nums) {
            seen.insert(n);
        }

        for (int x : seen) {
            // check if the number is the start of a sequence
            if (seen.find(x - 1) == seen.end()) {
                int length = 0;
                while (seen.find(x + length) != seen.end()) {
                    length += 1;
                }
                longest = max(length, longest);
            }
        }


        return longest;
    }
};