#include <deque>
#include <utility>
#include <vector>

class Solution {
public:
    long long countNonDecreasingSubarrays(std::vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());

        std::deque<std::pair<int, int>> monotonicDeque;

        long long operations = 0;
        long long validSubarrays = 0;

        int right = n - 1;

        for (int left = n - 1; left >= 0; --left) {
            int count = 1;

            // Merge smaller values into the current value.
            while (!monotonicDeque.empty() && monotonicDeque.back().first < nums[left]) {
                const auto [value, frequency] = monotonicDeque.back();
                monotonicDeque.pop_back();

                operations += 1LL * (nums[left] - value) * frequency;

                count += frequency;
            }

            monotonicDeque.emplace_back(nums[left], count);

            // Shrink the window until its operation cost is valid.
            while (operations > k) {
                operations -= monotonicDeque.front().first - nums[right];

                --monotonicDeque.front().second;

                if (monotonicDeque.front().second == 0) {
                    monotonicDeque.pop_front();
                }

                --right;
            }

            validSubarrays += right - left + 1;
        }

        return validSubarrays;
    }
};