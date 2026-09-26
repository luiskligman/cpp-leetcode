#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int top = 0;
        int bot = rows - 1;
        int row = -1;

        while (top <= bot) {
            row = (top + bot) / 2;
            if (target > matrix[row][cols - 1]) {
                top = row + 1;
            } else if (target < matrix[row][0]) {
                bot = row - 1;
            } else {
                break;
            }
        }

        // while loop exited without finding the row that may contain target
        if (top > bot) {
            return false;
        }

        int l = 0;
        int r = cols - 1;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (target > matrix[row][mid]) {
                l = mid + 1;
            } else if (target < matrix[row][mid]) {
                r = mid - 1;
            } else {
                return true;
            }
        }

        return false;
    }
};