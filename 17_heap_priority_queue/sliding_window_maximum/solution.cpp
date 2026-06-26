#include <vector>
#include <deque>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        const int size = static_cast<int>(nums.size());

        std::deque<int> window;
        std::vector<int> maximums;
        maximums.reserve(size - k + 1);

        for (int index = 0; index < size; ++index) {
            // Remove indices outside current window
            while (!window.empty() &&
                   window.front() <= index - k) {
                window.pop_front();
            }

            // Maintain decreasing order
            while (!window.empty() &&
                   nums[window.back()] <= nums[index]) {
                window.pop_back();
            }

            window.push_back(index);

            // Window becomes valid after first k elements
            if (index >= k - 1) {
                maximums.push_back(nums[window.front()]);
            }
        }

        return maximums;
    }
};