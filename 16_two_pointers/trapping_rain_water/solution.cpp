#include <vector>
#include <algorithm>

class Solution {
public:
    int trap(std::vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;

        int leftMax = 0;
        int rightMax = 0;

        int trappedWater = 0;

        while (left < right) {
            leftMax = std::max(leftMax, height[left]);
            rightMax = std::max(rightMax, height[right]);

            if (leftMax <= rightMax) {
                trappedWater += leftMax - height[left];
                ++left;
            } else {
                trappedWater += rightMax - height[right];
                --right;
            }
        }

        return trappedWater;
    }
};