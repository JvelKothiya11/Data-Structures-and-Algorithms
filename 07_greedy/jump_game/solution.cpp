#include <vector>
#include <algorithm>

class Solution {
public:
    bool canJump(const std::vector<int>& nums) {
        const int size = static_cast<int>(nums.size());
        int farthestReachable = 0;

        for (int index = 0; index < size; ++index) {
            if (index > farthestReachable) {
                return false;
            }

            farthestReachable = std::max(farthestReachable, index + nums[index]);
            if (farthestReachable >= size - 1) {
                return true;
            }
        }

        return true;
    }
};