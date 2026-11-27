class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st{};
        int longest{};

        // "()(()"
        // st      : -1, 2,
        // longest : 2, (4 - 2) = 2

        st.push(-1); // marker, index just before the current valid stretch

        for (int i = 0; i < static_cast<int>(s.length()); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i); // unmatched ')' becomes the new index marker
                } else {
                    longest = max(longest, i - st.top());
                }
            }
        }
        return longest;
    }
};
