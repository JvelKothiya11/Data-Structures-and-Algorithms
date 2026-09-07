#include <algorithm>
#include <vector>

class Solution {
public:
    int maxCoins(const std::vector<int>& nums) {
        const int n = static_cast<int>(nums.size());

        std::vector<int> balloons(n + 2, 1);
        for (int i = 0; i < n; ++i) {
            balloons[i + 1] = nums[i];
        }

        std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));

        for (int left = n - 1; left >= 0; --left) {
            for (int right = left + 2; right <= n + 1; ++right) {
                for (int last = left + 1; last < right; ++last) {
                    const int coins = dp[left][last] + dp[last][right] + balloons[left] * balloons[last] * balloons[right];
                    dp[left][right] = std::max(dp[left][right], coins);
                }
            }
        }

        return dp[0][n + 1];
    }
};