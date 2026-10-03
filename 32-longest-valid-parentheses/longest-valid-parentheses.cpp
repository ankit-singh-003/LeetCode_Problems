#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        st.push(-1); // Base boundary marker
        int max_len = 0;

        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    // Reset boundary if stack becomes empty
                    st.push(i);
                } else {
                    // Length of valid substring ending at index i
                    max_len = std::max(max_len, i - st.top());
                }
            }
        }

        return max_len;
    }
};