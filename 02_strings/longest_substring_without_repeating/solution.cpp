#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s) {
        std::vector<int> lastSeen(256, -1);

        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            left = std::max(left, lastSeen[s[right]] + 1);

            maxLength = std::max(maxLength, right - left + 1);
            lastSeen[s[right]] = right;
        }

        return maxLength;
    }
};