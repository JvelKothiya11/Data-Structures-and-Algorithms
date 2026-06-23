#include <algorithm>
#include <vector>

class Solution {
public:
    int maxSubArray(const std::vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            currentSum = std::max(nums[i], currentSum + nums[i]);
            maxSum = std::max(maxSum, currentSum);
        }

        return maxSum;
    }
};