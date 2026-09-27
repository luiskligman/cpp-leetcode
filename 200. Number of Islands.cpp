#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0) {
            return false;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        int islands = 0;

        auto bfs = [&](int r, int c) {
            deque<pair<int, int>> q;
            grid[r][c] = '0';
            q.push_back({r, c});

            while (!q.empty()) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop_front();

                if ((row + 1) < rows && grid[row + 1][col] == '1') {
                    grid[row + 1][col] = '0';
                    q.push_back({row + 1, col});
                }
                if ((col + 1) < cols && grid[row][col + 1] == '1') {
                    grid[row][col + 1] = '0';
                    q.push_back({row, col + 1});
                }
                if ((row - 1) >= 0 && grid[row - 1][col] == '1') {
                    grid[row - 1][col] = '0';
                    q.push_back({row - 1, col});
                }
                if ((col - 1) >= 0 && grid[row][col - 1] == '1') {
                    grid[row][col - 1] = '0';
                    q.push_back({row, col - 1});
                }
            }
        };

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1') {
                    bfs(i, j);
                    islands += 1;
                }
            }
        }

        return islands;
    }
};