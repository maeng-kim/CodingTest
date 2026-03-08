class Solution {
public:
    unordered_map<char, char> match = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    stack<char> st;

    bool isValid(string s) {
        for (char c : s) {
            if (c=='(' || c=='[' || c=='{') {
                st.push(c);
            }
            else {
                if (st.empty()) return false;
                if (st.top() != match[c]) return false;
                st.pop();
            }
        }
        return st.empty();
    }
};