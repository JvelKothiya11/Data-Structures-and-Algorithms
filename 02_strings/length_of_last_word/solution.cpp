#include <string>

class Solution {
public:
    int lengthOfLastWord(const std::string& s) {
        int index = static_cast<int>(s.size()) - 1;

        while (index >= 0 && s[index] == ' ') {
            --index;
        }
        int length = 0;

        while (index >= 0 && s[index] != ' ') {
            ++length;
            --index;
        }

        return length;
    }
};