#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // Boyer-Moore approach - iterate through each element. Each element is
        // a contender, if n is not the current contender than -- the count, if
        // it is ++ the count. In the end, the majority number survives
        int contender = nums.front();
        int count = 0;

        for (int n : nums) {
            if (n == contender) {
                count++;
            } else if (count == 0) {
                contender = n;
                count++;
            } else {
                count--;
            }
        }

        return contender;
    }
};
