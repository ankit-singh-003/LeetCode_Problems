class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        // Build the original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> last(26, -1);

        vector<int> prev(n, -1);

        function<void(int)> dfs = [&](int u) {

            int c = s[u] - 'a';

            // Remember previous ancestor with same character
            prev[u] = last[c];

            // Current node becomes the latest occurrence
            last[c] = u;

            // Visit children
            for (int v : adj[u]) {
                dfs(v);
            }

            // Restore the previous occurrence
            last[c] = prev[u];

            // Find the new parent
            int p;

            if (prev[u] != -1) {
                p = prev[u];
            } 
            else {
                p = parent[u];
            }

            // Add subtree size to the new parent
            if (p != -1) {
                ans[p] += ans[u];
            }
        };

        dfs(0);

        return ans;
    }
};