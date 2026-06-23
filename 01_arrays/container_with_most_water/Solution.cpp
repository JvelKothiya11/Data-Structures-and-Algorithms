#include <vector>
#include <algorithm>

class Solution {
public:
    int maxArea(const std::vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;

        long long maxWater = 0;

        while (left < right) {
            long long h = std::min(height[left], height[right]);
            long long width = right - left;
            maxWater = std::max(maxWater, h * width);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return static_cast<int>(maxWater);
    }
};