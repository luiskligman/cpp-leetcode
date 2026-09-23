#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;     // last element of nums1
        int j = n - 1;     // last element of nums2
        int k = m + n - 1; // last slot of nums1

        // fill in the largest values first, doing a two pointer approach on
        // valid initial digits in nums1 and nums2
        while (j >= 0) {
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
    }
};