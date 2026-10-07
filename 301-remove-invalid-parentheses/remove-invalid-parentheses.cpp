class Solution {
public:
    vector<string> ans;

    void dfs(const string& s, int i,
             int leftRemove, int rightRemove,
             int balance, string& cur) {

        if (i == s.size()) {
            if (leftRemove == 0 &&
                rightRemove == 0 &&
                balance == 0) {
                ans.push_back(cur);
            }
            return;
        }

        char c = s[i];

        if (c == '(') {
            // Option 1: remove '('
            if (leftRemove > 0) {
                dfs(s, i + 1,
                    leftRemove - 1, rightRemove,
                    balance, cur);
            }

            // Option 2: keep '('
            cur.push_back(c);
            dfs(s, i + 1,
                leftRemove, rightRemove,
                balance + 1, cur);
            cur.pop_back();
        }
        else if (c == ')') {
            // Option 1: remove ')'
            if (rightRemove > 0) {
                dfs(s, i + 1,
                    leftRemove, rightRemove - 1,
                    balance, cur);
            }

            // Option 2: keep ')'
            if (balance > 0) {
                cur.push_back(c);
                dfs(s, i + 1,
                    leftRemove, rightRemove,
                    balance - 1, cur);
                cur.pop_back();
            }
        }
        else {
            // Letters must be kept
            cur.push_back(c);
            dfs(s, i + 1,
                leftRemove, rightRemove,
                balance, cur);
            cur.pop_back();
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0;
        int rightRemove = 0;

        // Calculate minimum required removals
        for (char c : s) {
            if (c == '(') {
                leftRemove++;
            }
            else if (c == ')') {
                if (leftRemove > 0)
                    leftRemove--;
                else
                    rightRemove++;
            }
        }

        string cur;
        dfs(s, 0, leftRemove, rightRemove, 0, cur);

        // Different removal choices can produce the same string.
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};