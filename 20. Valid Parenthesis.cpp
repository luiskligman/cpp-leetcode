#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> open;
        unordered_map<char, char> match = {{')', '('}, {'}', '{'}, {']', '['}};

        for (const auto c : s) {
            if (c == ')' || c == '}' || c == ']') {
                // we cannot close what is not yet open
                if (open.empty() || open.top() != match[c]) {
                    return false;
                }
                open.pop();

            } else {
                open.push(c);
            }
        }

        return open.empty();
    }
};