#include <string>
#include <algorithm>

class Solution {
public:
    std::string reverseWords(std::string s) {
        std::reverse(s.begin(), s.end());

        const int size = static_cast<int>(s.size());
        std::string result;

        int index = 0;

        while (index < size) {
            while (index < size && s[index] == ' ') {
                ++index;
            }

            if (index >= size) {
                break;
            }

            const int start = index;

            while (index < size && s[index] != ' ') {
                ++index;
            }

            if (!result.empty()) {
                result += ' ';
            }

            for (int position = index - 1; position >= start; --position) {
                result += s[position];
            }
        }

        return result;
    }
};