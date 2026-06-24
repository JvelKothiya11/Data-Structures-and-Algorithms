#include <vector>
#include <algorithm>

class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        const int size = static_cast<int>(nums.size());
        int pivotIndex = size - 2;

        while (pivotIndex >= 0 && nums[pivotIndex] >= nums[pivotIndex + 1]) {
            --pivotIndex;
        }

        if (pivotIndex >= 0) {
            int successorIndex = size - 1;
            while (nums[successorIndex] <= nums[pivotIndex]) {
                --successorIndex;
            }
            std::swap(nums[pivotIndex], nums[successorIndex]);
        }

        std::reverse(nums.begin() + pivotIndex + 1, nums.end());
    }
};