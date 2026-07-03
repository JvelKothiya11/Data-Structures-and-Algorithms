#include <string>

class Solution {
public:
    int strStr(const std::string& haystack, const std::string& needle) {
        if (needle.empty()) {
            return 0;
        }

        const int haystackLength = static_cast<int>(haystack.size());
        const int needleLength = static_cast<int>(needle.size());

        if (needleLength > haystackLength) {
            return -1;
        }

        for (int startIndex = 0; startIndex <= haystackLength - needleLength; ++startIndex) {
            int offset = 0;

            while (offset < needleLength && haystack[startIndex + offset] == needle[offset]) {
                ++offset;
            }

            if (offset == needleLength) {
                return startIndex;
            }
        }

        return -1;
    }
};