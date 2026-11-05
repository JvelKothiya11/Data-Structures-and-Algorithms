#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution {
public:
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d) {
        std::sort(arr2.begin(), arr2.end());

        int distanceValue = 0;

        for (const int value : arr1) {
            const auto it = std::lower_bound(arr2.begin(), arr2.end(), value);

            const bool hasRightCandidate = it != arr2.end() && std::abs(value - *it) <= d;

            const bool hasLeftCandidate = it != arr2.begin() && std::abs(value - *(it - 1)) <= d;

            if (!hasRightCandidate && !hasLeftCandidate) {
                ++distanceValue;
            }
        }

        return distanceValue;
    }
};