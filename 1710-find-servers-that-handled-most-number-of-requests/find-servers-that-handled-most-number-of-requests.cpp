class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        
        set<int> available;
        
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> busy;

        vector<int> cnt(k, 0);

        for (int i = 0; i < arrival.size(); i++) {

            // Release completed servers
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // If no server is available
            if (available.empty()) {
                continue;
            }

            // Find preferred server
            int preferred = i % k;

            auto it = available.lower_bound(preferred);

            // Circular allocation
            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;

            // Assign request
            available.erase(it);
            cnt[server]++;

            // Update finishing time
            busy.push({arrival[i] + load[i], server});
        }

        // Find maximum requests handled
        int maxi = *max_element(cnt.begin(), cnt.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (cnt[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};