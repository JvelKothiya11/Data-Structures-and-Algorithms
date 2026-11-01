#include <string>

class Solution {
public:
    bool isSubsequence(const std::string& s, const std::string& t) {
        const int sLength = static_cast<int>(s.size());
        const int tLength = static_cast<int>(t.size());

        int sIndex = 0;
        int tIndex = 0;

        while (sIndex < sLength && tIndex < tLength) {
            if (s[sIndex] == t[tIndex]) {
                ++sIndex;
            }

            ++tIndex;
        }

        return sIndex == sLength;
    }
};