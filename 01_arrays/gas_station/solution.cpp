#include <vector>

class Solution {
public:
    int canCompleteCircuit(const std::vector<int>& gas, const std::vector<int>& cost) {
        const int n = static_cast<int>(gas.size());

        int totalBalance = 0;
        int currentBalance = 0;
        int startIndex = 0;

        for (int i = 0; i < n; ++i) {
            const int balance = gas[i] - cost[i];

            totalBalance += balance;
            currentBalance += balance;

            if (currentBalance < 0) {
                currentBalance = 0;
                startIndex = i + 1;
            }
        }

        return totalBalance >= 0 ? startIndex : -1;
    }
};