#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> stack;
        int a {0};
        int b {0};

        for (const auto& c : tokens) {
            if (c == "+") {
                a = stack.back(); stack.pop_back();
                b = stack.back(); stack.pop_back();
                stack.push_back(a + b);
            } else if (c == "-") {
                a = stack.back(); stack.pop_back();
                b = stack.back(); stack.pop_back();
                stack.push_back(b - a);
            } else if (c == "*") {
                a = stack.back(); stack.pop_back();
                b = stack.back(); stack.pop_back();
                stack.push_back(a * b);
            } else if (c == "/") {
                a = stack.back(); stack.pop_back();
                b = stack.back(); stack.pop_back();
                stack.push_back(b / a);
            } else {
                stack.push_back(stoi(c));
            }
        }
        return stack.back();
    }
};