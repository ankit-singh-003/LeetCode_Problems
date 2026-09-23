class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int totalSum = 0;

        for (int num : nums)
            totalSum += num;

        int target = totalSum - x;

        // If target is negative, impossible
        if (target < 0)
            return -1;

        // target = 0 means remove all elements
        if (target == 0)
            return nums.size();

        int left = 0;
        int sum = 0;
        int maxLen = -1;

        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];

            while (sum > target && left <= right) {
                sum -= nums[left];
                left++;
            }

            if (sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }

        return maxLen == -1 ? -1 : nums.size() - maxLen;
    }
};