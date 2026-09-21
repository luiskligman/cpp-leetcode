#include <bits/stdc++.h>
using namespace std;

// O(1) time complexity
// O(1) extra space, O(81) for this input, noramlizes to O(n^2) for large input
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        unordered_set<int> rows[9];
        unordered_set<int> cols[9];
        unordered_set<int> boxes[9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') continue;
                if (rows[i].count(board[i][j]) || cols[j].count(board[i][j]) ||
                    boxes[(i / 3) * 3 + (j / 3)].count(board[i][j])) {
                    return false;
                } else {
                    rows[i].insert(board[i][j]);
                    cols[j].insert(board[i][j]);
                    boxes[(i / 3) * 3 + (j / 3)].insert(board[i][j]);
                }
            }
        }

        return true;
    }
};