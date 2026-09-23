#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() == 0) { return 0; }

        int l = 0;
        int r = height.size() - 1;

        int leftMax = height[l];
        int rightMax = height[r];
    
        int ret = 0;

        while (l < r) {
            // the left side it to small, limiting us from trapping water, increment its pointer
            if (leftMax < rightMax) {
                l += 1;  // increment pointer
                leftMax = max(leftMax, height[l]);  // update the max if applicable at new height index
                ret += leftMax - height[l];  // if the current height is less than the max, we can trap water, since leftMax is known to be less than rightMax, so rightMax will trap water
            } else {
                // rightMax < leftMax || rightMax == leftMax
                r -= 1;  // bring r pointer closer to l
                rightMax = max(rightMax, height[r]);  // re-calculate if this index has a new max 
                ret += rightMax - height[r];
            }
        }
        return ret;
    }
};