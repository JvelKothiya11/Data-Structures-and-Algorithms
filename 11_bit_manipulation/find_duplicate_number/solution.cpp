#include <vector>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        int slowPointer = nums[0];
        int fastPointer = nums[0];

        do {
            slowPointer = nums[slowPointer];
            fastPointer = nums[nums[fastPointer]];
        } while (slowPointer != fastPointer);

        int cycleStart = nums[0];

        while (cycleStart != slowPointer) {
            cycleStart = nums[cycleStart];
            slowPointer = nums[slowPointer];
        }

        return cycleStart;
    }
};