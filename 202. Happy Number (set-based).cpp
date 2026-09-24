#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        while (true) {
            if (n == 1) { return true; }
            if (seen.count(n)) {
                // already been at this value
                return false;
            } else {
                seen.insert(n);
                int temp = 0;
                while (n > 0) {
                    int i = n % 10;
                    temp += i * i;
                    n /= 10;
                }
                n = temp;
            }
        }
        return false;
    }
};