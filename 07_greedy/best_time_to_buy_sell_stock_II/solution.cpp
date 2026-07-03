#include <vector>

class Solution {
public:
    int maxProfit(const std::vector<int>& prices) {
        const int size = static_cast<int>(prices.size());
        int totalProfit = 0;

        for (int day = 1; day < size; ++day) {
            const int dailyProfit = prices[day] - prices[day - 1];
            if (dailyProfit > 0) {
                totalProfit += dailyProfit;
            }
        }

        return totalProfit;
    }
};