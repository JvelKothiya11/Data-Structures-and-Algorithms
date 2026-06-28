#include <vector>
#include <string>

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& strs) {
        const int wordCount = static_cast<int>(strs.size());

        for (int column = 0; column < static_cast<int>(strs[0].size()); ++column) {
            const char expected = strs[0][column];
            for (int row = 1; row < wordCount; ++row) {
                if (column >= static_cast<int>(strs[row].size()) || strs[row][column] != expected) {
                    return strs[0].substr(0, column);
                }
            }
        }

        return strs[0];
    }
};