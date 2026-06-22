#include <vector>

class Solution {
public:
    std::vector<int> findMissingAndRepeatedValues(const std::vector<std::vector<int>>& grid) {
        long long n = grid.size();
        long long N = n * n;

        long long current_sum = 0;
        long long current_sq_sum = 0;

        for (const auto& row : grid) {
            for (int val : row) {
                current_sum += val;
                current_sq_sum += 1LL * val * val;
            }
        }

        long long expected_sum = N * (N + 1) / 2;
        long long expected_sq_sum = N * (N + 1) * (2 * N + 1) / 6;

        long long diff = current_sum - expected_sum;
        long long sq_diff = current_sq_sum - expected_sq_sum;

        long long sum = sq_diff / diff;

        int repeated = static_cast<int>((sum + diff) / 2);
        int missing  = static_cast<int>((sum - diff) / 2);

        return {repeated, missing};
    }
};
