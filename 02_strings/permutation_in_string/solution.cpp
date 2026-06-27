#include <string>
#include <array>

class Solution {
public:
    bool checkInclusion(const std::string& s1, const std::string& s2) {
        const int windowSize = static_cast<int>(s1.size());
        const int size = static_cast<int>(s2.size());

        if (windowSize > size) {
            return false;
        }

        std::array<int, 26> balance{};

        for (char ch : s1) {
            ++balance[ch - 'a'];
        }
        int remaining = windowSize;

        for (int right = 0; right < size; ++right) {
            if (balance[s2[right] - 'a']-- > 0) {
                --remaining;
            }
            if (right >= windowSize) {
                if (++balance[s2[right - windowSize] - 'a'] > 0) {
                    ++remaining;
                }
            }

            if (remaining == 0) {
                return true;
            }
        }

        return false;
    }
};