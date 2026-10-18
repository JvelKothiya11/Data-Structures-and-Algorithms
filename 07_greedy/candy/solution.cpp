#include <algorithm>
#include <vector>

class Solution {
public:
    int candy(const std::vector<int>& ratings) {
        const int n = static_cast<int>(ratings.size());

        if (n == 0) {
            return 0;
        }

        std::vector<int> candies(n, 1);

        // Left-to-right: satisfy increasing ratings from the left.
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Right-to-left: satisfy decreasing ratings from the right.
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(
                    candies[i],
                    candies[i + 1] + 1
                );
            }
        }

        int totalCandies = 0;
        for (const int candyCount : candies) {
            totalCandies += candyCount;
        }

        return totalCandies;
    }
};