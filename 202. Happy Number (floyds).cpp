#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(log n)
// Space Complexity: O(1) extra space
class Solution {
public:
    // O(log n) function
    int sumOfSquares(int n) {
        int temp = 0;
        while (n > 0) {
            int i = n % 10;
            temp += i * i;
            n /= 10;
        }
        return temp;
    }

    bool isHappy(int n) {

        if (n == 1) {
            return true;
        }
        int slow = sumOfSquares(n);
        int fast = sumOfSquares(sumOfSquares(n));

        while (true) {
            if (fast == 1) {
                return true;
            } // fast is ahead of slow so if no cycle, it will reach 1 first
            if (slow == fast) {
                return false;
            } // floyd tortoise and haire cycle
            slow = sumOfSquares(slow);
            fast = sumOfSquares(sumOfSquares(fast));
        }
    }
};