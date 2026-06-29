#include <vector>

class Solution {
public:
    int peakIndexInMountainArray(const std::vector<int>& arr) {
        int left = 0;
        int right = static_cast<int>(arr.size()) - 1;

        while (left < right) {
            const int mid = left + (right - left) / 2;
            const bool ascending = arr[mid] < arr[mid + 1];
            if (ascending) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};