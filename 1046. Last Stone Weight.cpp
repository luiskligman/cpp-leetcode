class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq(stones.begin(), stones.end());

        while (pq.size() > 1) {
            int s1{pq.top()};
            pq.pop();
            int s2{pq.top()};
            pq.pop();

            // destroy both, push nothing
            if (s1 == s2) {
                continue;
            }

            // only push a stone of the remainder
            pq.push(abs(s1 - s2)); // s1 != s2
        }

        if (!pq.empty()) {
            return pq.top();
        } // pq should only have one or less items at this point

        return 0;
    }
};
