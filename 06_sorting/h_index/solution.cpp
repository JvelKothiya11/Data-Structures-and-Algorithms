#include <vector>
#include <algorithm>

class Solution {
public:
    int hIndex(std::vector<int>& citations) {
        std::sort(citations.rbegin(), citations.rend());

        const int size = static_cast<int>(citations.size());

        for (int index = 0; index < size; ++index) {
            if (citations[index] < index + 1) {
                return index;
            }
        }

        return size;
    }
};