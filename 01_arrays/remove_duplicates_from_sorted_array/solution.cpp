#include <vector>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        int writeIndex = 0;
        for (const int value : nums) {
            if (writeIndex < 2 || nums[writeIndex - 2] != value) {
                nums[writeIndex++] = value;
            }
        }

        return writeIndex;
    }
};