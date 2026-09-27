#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        int area = 0;

        auto bfs = [&](int r, int c) {
            queue<pair<int, int>> q;
            grid[r][c] = 0;
            q.push({r, c});
            int island_area = 0;

            while (!q.empty()) {
                int row = q.front().first;
                int col = q.front().second;
                q.pop();
                island_area += 1;

                if ((row + 1) < rows && grid[row + 1][col] == 1) {
                    grid[row + 1][col] = 0;
                    q.push({row + 1, col});
                }
                if ((col + 1) < cols && grid[row][col + 1] == 1) {
                    grid[row][col + 1] = 0;
                    q.push({row, col + 1});
                }
                if ((row - 1) >= 0 && grid[row - 1][col] == 1) {
                    grid[row - 1][col] = 0;
                    q.push({row - 1, col});
                }
                if ((col - 1) >= 0 && grid[row][col - 1] == 1) {
                    grid[row][col - 1] = 0;
                    q.push({row, col - 1});
                }
            }
            area = max(area, island_area);
        };

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    bfs(i, j);
                }
            }
        }

        return area;
    }
};