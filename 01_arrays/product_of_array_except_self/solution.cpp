#include <vector>

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        const int size = static_cast<int>(nums.size());

        std::vector<int> result(size, 1);

        for (int index = 1; index < size; ++index) {
            result[index] = result[index - 1] * nums[index - 1];
        }

        int suffixProduct = 1;

        for (int index = size - 1; index >= 0; --index) {
            result[index] *= suffixProduct;
            suffixProduct *= nums[index];
        }

        return result;
    }
};