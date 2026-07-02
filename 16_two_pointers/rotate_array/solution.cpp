#include <vector>
#include <algorithm>

class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        const int size = static_cast<int>(nums.size());
        if (size == 0) {
            return;
        }
        k %= size;
        if (k == 0) {
            return;
        }

        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};