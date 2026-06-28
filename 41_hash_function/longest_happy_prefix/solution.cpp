#include <string>
#include <vector>

class Solution {
public:
    std::string longestPrefix(const std::string& s) {
        const int size = static_cast<int>(s.size());

        if (size == 0) {
            return "";
        }
        std::vector<int> longestPrefixSuffix(size, 0);
        int matchedLength = 0;

        for (int index = 1; index < size; ) {
            if (s[index] == s[matchedLength]) {
                longestPrefixSuffix[index] = ++matchedLength;
                ++index;
            } else if (matchedLength > 0) {
                matchedLength = longestPrefixSuffix[matchedLength - 1];
            } else {
                ++index;
            }
        }

        return s.substr(0, longestPrefixSuffix.back());
    }
};