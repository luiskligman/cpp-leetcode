#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0;
        int end = numbers.size() - 1;

        // can use two pointer approach since input is sorted
        while (end > start) {
            int result = numbers[start] + numbers[end];

            if (result > target) {
                end--;
            } else if (result < target) {
                start++;
            } else {
                break;
            }
        }
        // 1 indexed, add 1 when returning indicies
        return vector<int>{start + 1, end + 1};
    }
};