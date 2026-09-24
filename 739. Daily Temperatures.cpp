#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n)
// Extra Space Complexity: O(n)
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int size = temperatures.size();
        vector<int> output(size);
        stack<int> index;
        output[size - 1] = 0;
        index.push(size - 1);

        for (int i = size - 2; i >= 0; i--) {
            while (!index.empty() &&
                   temperatures[i] >= temperatures[index.top()]) {
                index.pop();
            } // now temps[i] < temps[index.top()] or index is empty
            if (index.empty()) {
                output[i] = 0;
                index.push(i);
            } else {
                // index is not empty and temps[i] <= temps[index.top()]
                output[i] = index.top() - i;
                index.push(i);
            }
        }
        return output;
    }
};