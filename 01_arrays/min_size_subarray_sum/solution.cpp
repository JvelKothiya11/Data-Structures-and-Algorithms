#include <algorithm>
#include <climits>
#include <vector>

class Solution {
public:
    int minSubArrayLen(int target, const std::vector<int>& nums) {
        const int n = static_cast<int>(nums.size());

        int left = 0;
        int windowSum = 0;
        int minLength = INT_MAX;

        for (int right = 0; right < n; ++right) {
            windowSum += nums[right];

            while (windowSum >= target) {
                minLength = std::min(minLength, right - left + 1);
                windowSum -= nums[left];
                ++left;
            }
        }

        return minLength == INT_MAX ? 0 : minLength;
    }
};