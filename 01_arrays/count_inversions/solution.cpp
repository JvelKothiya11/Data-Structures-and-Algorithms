#include <vector>

class Solution {
private:
    long long mergeAndCount(std::vector<int>& values, int left, int mid, int right) {
        std::vector<int> merged;
        merged.reserve(right - left + 1);

        int leftIndex = left;
        int rightIndex = mid + 1;

        long long inversionCount = 0;

        while (leftIndex <= mid && rightIndex <= right) {
            if (values[leftIndex] <= values[rightIndex]) {
                merged.push_back(values[leftIndex++]);
            } else {
                merged.push_back(values[rightIndex++]);
                inversionCount += (mid - leftIndex + 1);
            }
        }

        while (leftIndex <= mid) {
            merged.push_back(values[leftIndex++]);
        }

        while (rightIndex <= right) {
            merged.push_back(values[rightIndex++]);
        }

        for (int index = left; index <= right; ++index) {
            values[index] = merged[index - left];
        }

        return inversionCount;
    }

    long long countInversions( std::vector<int>& values, int left, int right) {
        if (left >= right) {
            return 0;
        }
        const int mid = left + (right - left) / 2;
        return countInversions(values, left, mid) + countInversions(values, mid + 1, right) + mergeAndCount(values, left, mid, right);
    }

public:
    long long inversionCount(std::vector<int>& arr) {
        return countInversions(arr, 0, static_cast<int>(arr.size()) - 1);
    }
};