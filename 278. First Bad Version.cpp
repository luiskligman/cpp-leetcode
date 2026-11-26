// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l {1};
        int r {n};
        int ans {};

        while (l <= r) {
            // (l + r) / 2 -> (2l - l + r) / 2 -> l + (r - l) / 2
            // l + (r - l) / 2  this form stops overflow
            int m = l + (r - l) / 2;
            if (isBadVersion(m)) {
                r = m - 1;
                ans = m;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }
};
