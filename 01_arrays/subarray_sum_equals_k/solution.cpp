#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;

        int prefixSum = 0;
        int subarrayCount = 0;

        for (const int value : nums) {
            prefixSum += value;

            auto it = prefixCount.find(prefixSum - k);
            if (it != prefixCount.end()) {
                subarrayCount += it->second;
            }

            ++prefixCount[prefixSum];
        }

        return subarrayCount;
    }
};