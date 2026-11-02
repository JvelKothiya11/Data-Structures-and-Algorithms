#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution {
public:
    int minMoves2(std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        const int n = static_cast<int>(nums.size());
        const int median = nums[n / 2];

        int totalMoves = 0;

        for (const int value : nums) {
            totalMoves += std::abs(value - median);
        }

        return totalMoves;
    }
};