#include <vector>
#include <algorithm>

class Solution {
public:
    int jump(const std::vector<int>& nums) {
        const int size = static_cast<int>(nums.size());

        int jumpCount = 0;
        int currentRangeEnd = 0;
        int farthestReachable = 0;

        for (int index = 0; index < size - 1; ++index) {
            farthestReachable = std::max(farthestReachable,index + nums[index]);

            if (index == currentRangeEnd) {
                ++jumpCount;
                currentRangeEnd = farthestReachable;
            }
        }

        return jumpCount;
    }
};