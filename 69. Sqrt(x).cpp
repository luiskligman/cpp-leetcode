class Solution {
public:
    int mySqrt(int x) {
        int l{};
        int r{x};
        int ans{};

        while (l <= r) {
            int m = (r + l) / 2;
            if (static_cast<long long>(m) * m <= x) {
                // m fits, try larger
                ans = m;
                l = m + 1;
            } else {
                // m is too big
                r = m - 1;
            }
        }
        return ans;
    }
};
