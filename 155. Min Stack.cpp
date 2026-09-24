#include <bits/stdc++.h>
using namespace std;

class MinStack {
public:
    MinStack() {}

    void push(int value) {
        s_.push(value);
        if (min_.empty() || value < min_.top()) {
            min_.push(value);
        } else {
            min_.push(min_.top());
        }
    }

    void pop() {
        s_.pop();
        min_.pop();
    }

    int top() { return s_.top(); }

    int getMin() { return min_.top(); }

private:
    stack<int> s_;
    stack<int> min_; // separate stack to contain the min value at each step
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */