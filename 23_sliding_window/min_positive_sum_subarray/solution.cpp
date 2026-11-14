#include <algorithm>
#include <climits>
#include <set>
#include <vector>

class Solution {
public:
    int minimumSumSubarray(std::vector<int>& nums, int l, int r) {
        const int n = static_cast<int>(nums.size());

        std::vector<long long> prefixSum(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        long long minimumSum = LLONG_MAX;
        std::multiset<long long> prefixWindow;

        for (int right = l; right <= n; ++right) {
            // Add the prefix sum corresponding to a subarray of length l.
            prefixWindow.insert(prefixSum[right - l]);

            // Find the largest prefix sum strictly smaller than prefixSum[right].
            auto it = prefixWindow.lower_bound(prefixSum[right]);

            if (it != prefixWindow.begin()) {
                --it;

                minimumSum = std::min(minimumSum, prefixSum[right] - *it);
            }

            // Remove prefix sums that would produce subarrays longer than r.
            if (right >= r) {
                const auto expired = prefixWindow.find(prefixSum[right - r]);

                prefixWindow.erase(expired);
            }
        }

        return minimumSum == LLONG_MAX ? -1 : static_cast<int>(minimumSum);
    }
};