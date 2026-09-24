#include <bits/stdc++.h>
using namespace std;

// Spent an hour on this problem: need to review
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = heights[0];
        stack<int> s; // index
        s.push(0);

        // heights vector guaranteed to not be empty
        for (int i = 1; i < n; i++) {
            while (!s.empty() && heights[s.top()] > heights[i]) {
                int index = s.top();
                int height = heights[s.top()];
                s.pop();
                int width = s.empty() ? i : (i - s.top() - 1);
                maxArea = max(maxArea, height * width);
            }
            s.push(i);
        }

        // A bar only gets popped when something shorter appears to its right
        while (!s.empty()) {
            int height = heights[s.top()];
            s.pop();
            int width = s.empty() ? n : (n - s.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        return maxArea;
    }
};