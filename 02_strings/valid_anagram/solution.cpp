#include <string>
#include <array>

class Solution {
public:
    bool isAnagram(const std::string& s, const std::string& t) {
        if (s.size() != t.size()) {
            return false;
        }

        std::array<int, 256> frequency{};

        for (unsigned char ch : s) {
            ++frequency[ch];
        }

        for (unsigned char ch : t) {
            if (--frequency[ch] < 0) {
                return false;
            }
        }

        return true;
    }
};