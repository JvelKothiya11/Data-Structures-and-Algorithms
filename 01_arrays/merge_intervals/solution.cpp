#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> mergedIntervals;

        for (const auto& interval : intervals) {
            if (mergedIntervals.empty() || interval[0] > mergedIntervals.back()[1]) {
                mergedIntervals.push_back(interval);
            } else {
                mergedIntervals.back()[1] = std::max(mergedIntervals.back()[1], interval[1]);
            }
        }

        return mergedIntervals;
    }
};