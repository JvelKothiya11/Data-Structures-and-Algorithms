#include <vector>

class Solution {
public:
    int search(const std::vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            const int mid = left + (right - left) / 2;
            const int leftValue = nums[left];
            const int midValue = nums[mid];
            const int rightValue = nums[right];

            if (midValue == target) {
                return mid;
            }

            const bool leftHalfSorted = leftValue <= midValue;

            if (leftHalfSorted) {
                if (leftValue <= target && target < midValue) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (midValue < target && target <= rightValue) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};