#include <vector>

class Solution {
public:
    int singleNonDuplicate(const std::vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left < right) {
            int pairStart = left + (right - left) / 2;
            if (pairStart % 2 != 0) {
                --pairStart;
            }
            const bool validPair = nums[pairStart] == nums[pairStart + 1];

            if (validPair) {
                left = pairStart + 2;
            } else {
                right = pairStart;
            }
        }

        return nums[left];
    }
};