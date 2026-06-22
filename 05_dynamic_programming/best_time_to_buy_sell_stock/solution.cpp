#include <algorithm>
#include <vector>

class Solution {
public:
    int maxProfit(const std::vector<int>& prices) {
        int bestBuy = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < static_cast<int>(prices.size()); ++i) {
            maxProfit = std::max(maxProfit, prices[i] - bestBuy);
            bestBuy = std::min(bestBuy, prices[i]);
        }

        return maxProfit;
    }
};