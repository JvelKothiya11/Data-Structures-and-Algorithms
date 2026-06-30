#include <vector>
#include <climits>
#include <algorithm>

class Solution {
public:
    double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        const int size1 = static_cast<int>(nums1.size());
        const int size2 = static_cast<int>(nums2.size());
        const int total = size1 + size2;
        int left = 0;
        int right = size1;

        while (left <= right) {
            const int partition1 = left + (right - left) / 2;
            const int partition2 = (total + 1) / 2 - partition1;
            const int leftMax1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
            const int rightMin1 = (partition1 == size1) ? INT_MAX : nums1[partition1];
            const int leftMax2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
            const int rightMin2 = (partition2 == size2) ? INT_MAX : nums2[partition2];

            if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1) {
                if (total % 2 == 0) {
                    return (std::max(leftMax1, leftMax2) + std::min(rightMin1, rightMin2)) / 2.0;
                }
                return static_cast<double>(std::max(leftMax1, leftMax2));
            }

            if (leftMax1 > rightMin2) {
                right = partition1 - 1;
            } else {
                left = partition1 + 1;
            }
        }

        return 0.0;
    }
};