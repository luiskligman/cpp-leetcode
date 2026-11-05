class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        std::vector<int> ret {};
        std::unordered_map<int, int> seen {};

        for (const int& n : nums1) {
            ++seen[n];
        }

        for (const int& n : nums2) {
            auto it = seen.find(n);
            if (it != seen.end() && it->second > 0) {
                --seen[n];
                ret.push_back(n);
            }
        }
        return ret;
    }
};
