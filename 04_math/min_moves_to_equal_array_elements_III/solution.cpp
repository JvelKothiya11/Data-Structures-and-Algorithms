#include <algorithm>
#include <vector>

class Solution {
public:
    int minMoves(const std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        const int largest = *std::max_element(
            nums.begin(),
            nums.end()
        );

        int totalMoves = 0;

        for (const int value : nums) {
            totalMoves += largest - value;
        }

        return totalMoves;
    }
};