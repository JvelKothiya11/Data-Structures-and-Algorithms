#include <algorithm>
#include <climits>
#include <set>
#include <vector>

class Solution {
private:
    static constexpr long long INF = LLONG_MAX / 4;

    std::vector<long long> getMinOps(const std::vector<int>& nums, int windowSize) {
        const int n = static_cast<int>(nums.size());

        std::vector<long long> minOps;
        minOps.reserve(n - windowSize + 1);

        std::multiset<int> lower;
        std::multiset<int> upper;

        long long lowerSum = 0;
        long long upperSum = 0;

        for (int i = 0; i < n; ++i) {
            const int value = nums[i];

            // Insert the incoming element.
            if (lower.empty() || value <= *lower.rbegin()) {
                lower.insert(value);
                lowerSum += value;
            } else {
                upper.insert(value);
                upperSum += value;
            }

            // Remove the element leaving the window.
            if (i >= windowSize) {
                const int outgoing = nums[i - windowSize];

                const auto it = lower.find(outgoing);

                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= outgoing;
                } else {
                    const auto upperIt = upper.find(outgoing);
                    upper.erase(upperIt);
                    upperSum -= outgoing;
                }
            }

            // Maintain the median partition.
            if (lower.size() < upper.size()) {
                const int valueToMove = *upper.begin();

                upper.erase(upper.begin());
                lower.insert(valueToMove);

                upperSum -= valueToMove;
                lowerSum += valueToMove;
            } else if (lower.size() > upper.size() + 1) {
                const auto it = std::prev(lower.end());
                const int valueToMove = *it;

                lower.erase(it);
                upper.insert(valueToMove);

                lowerSum -= valueToMove;
                upperSum += valueToMove;
            }

            // Calculate the minimum operations for this window.
            if (i >= windowSize - 1) {
                const long long median = *lower.rbegin();

                const long long operations = median * static_cast<long long>(lower.size()) - lowerSum + upperSum - median * static_cast<long long>(upper.size());

                minOps.push_back(operations);
            }
        }

        return minOps;
    }

public:
    long long minOperations(const std::vector<int>& nums, int x, int k) {
        const int n = static_cast<int>(nums.size());

        if (k == 0) {
            return 0;
        }

        if (x <= 0 || 1LL * x * k > n) {
            return -1;
        }

        // Cost of making each window of length x equal.
        const std::vector<long long> minOps = getMinOps(nums, x);

        const int windowCount = static_cast<int>(minOps.size());

        // prev[i]: minimum cost to select (count - 1)
        // non-overlapping windows from positions i onward.
        std::vector<long long> prev(windowCount + 1, 0);
        std::vector<long long> curr(windowCount + 1, INF);

        for (int count = 1; count <= k; ++count) {
            std::fill(curr.begin(), curr.end(), INF);

            for (int i = windowCount - 1; i >= 0; --i) {
                // Option 1: Skip the current window.
                curr[i] = curr[i + 1];

                // Option 2: Select the current window.
                if (i + x <= windowCount && prev[i + x] != INF) {
                    curr[i] = std::min(curr[i], minOps[i] + prev[i + x]);
                }
            }

            prev.swap(curr);
        }

        return prev[0];
    }
};