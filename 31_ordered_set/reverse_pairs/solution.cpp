#include <vector>

class Solution {
private:
    void mergeSortedRanges(std::vector<int>& values, int left, int mid, int right) {
        std::vector<int> merged;
        merged.reserve(right - left + 1);

        int leftIndex = left;
        int rightIndex = mid + 1;

        while (leftIndex <= mid && rightIndex <= right) {
            if (values[leftIndex] <= values[rightIndex]) {
                merged.push_back(values[leftIndex++]);
            } else {
                merged.push_back(values[rightIndex++]);
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
    }

    int countReversePairs(const std::vector<int>& values, int left, int mid, int right) {
        int count = 0;
        int rightIndex = mid + 1;

        for (int leftIndex = left; leftIndex <= mid; ++leftIndex) {
            while (rightIndex <= right && static_cast<long long>(values[leftIndex]) > 2LL * values[rightIndex]) {
                ++rightIndex;
            }
            count += rightIndex - (mid + 1);
        }

        return count;
    }

    int mergeSortAndCount(std::vector<int>& values, int left, int right) {
        if (left >= right) {
            return 0;
        }
        const int mid = left + (right - left) / 2;

        int reversePairCount = 0;
        reversePairCount += mergeSortAndCount(values, left, mid);
        reversePairCount += mergeSortAndCount(values, mid + 1, right);
        reversePairCount += countReversePairs(values, left, mid, right);

        mergeSortedRanges(values, left, mid, right);
        return reversePairCount;
    }

public:
    int reversePairs(std::vector<int>& nums) {
        return mergeSortAndCount(nums, 0, static_cast<int>(nums.size()) - 1);
    }
};