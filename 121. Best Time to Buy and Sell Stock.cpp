#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) {
            return 0;
        }

        int maxProfit = 0;

        int l = 0;
        int r = 1;

        while (r < prices.size()) {

            maxProfit = max(maxProfit, prices[r] - prices[l]);

            if (prices[r] < prices[l]) {
                l = r;
            }
            r++;
        }

        return maxProfit;
    }
};