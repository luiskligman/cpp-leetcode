#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();  // normalize k since k can be greater than nums.size()

        reverse(nums.begin(), nums.end());  // reverse entire list
        reverse(nums.begin(), nums.begin() + k);  // reverse first subset of list up to k
        reverse(nums.begin() + k, nums.end());  // reverse second subset of list from k to end
    }
};