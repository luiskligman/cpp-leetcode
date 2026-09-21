#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        vector<vector<string>> output;

        unordered_map<string, vector<string>> strings;

        for (auto& s : strs) {
            string key = s;
            sort(key.begin(), key.end());

            // auto creates the bucket if new, appends the original
            strings[key].push_back(s);
        }

        for (const auto& s : strings) {
            output.push_back(s.second);
        }

        return output;
    }
};