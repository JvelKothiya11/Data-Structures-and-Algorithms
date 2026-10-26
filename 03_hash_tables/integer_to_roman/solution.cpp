#include <array>
#include <string>

class Solution {
public:
    std::string intToRoman(int num) {
        static constexpr std::array<int, 13> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        static constexpr std::array<const char*, 13> symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        std::string result;
        result.reserve(16);

        for (std::size_t i = 0; i < values.size(); ++i) {
            while (num >= values[i]) {
                num -= values[i];
                result += symbols[i];
            }
        }

        return result;
    }
};