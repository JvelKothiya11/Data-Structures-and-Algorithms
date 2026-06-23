#include <vector>
#include <algorithm>

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = static_cast<int>(nums.size()) - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                std::swap(nums[low++], nums[mid++]);
            } 
            else if (nums[mid] == 1) {
                mid++;
            } 
            else {
                std::swap(nums[mid], nums[high--]);
            }
        }
    }
};