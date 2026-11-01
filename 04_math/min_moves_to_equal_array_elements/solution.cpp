#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int minMoves(const std::vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        const int minValue = *std::min_element(
            nums.begin(),
            nums.end()
        );

        const int totalSum = std::accumulate(
            nums.begin(),
            nums.end(),
            0
        );

        return totalSum - minValue * static_cast<int>(nums.size());
    }
};