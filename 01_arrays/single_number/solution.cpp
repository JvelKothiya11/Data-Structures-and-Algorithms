#include <vector>

class Solution {
public:
    int singleNumber(const std::vector<int>& nums) {
        int xorResult = 0;

        for (int num : nums) {
            xorResult ^= num;
        }

        return xorResult;
    }
};