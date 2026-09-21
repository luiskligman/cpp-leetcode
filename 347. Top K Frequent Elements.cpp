#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        vector<int> output;

        unordered_map<int, int> count;
        for (const auto& n : nums) {
            count[n]++;
        }

        // use min heap
        // pair <frequency, int>
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            heap;

        for (auto& [val, freq] : count) {
            heap.push({freq, val});
            if (heap.size() > k)
                heap.pop();
        }

        while (!heap.empty()) {
            output.push_back(heap.top().second);
            heap.pop();
        }

        return output;
    }
};