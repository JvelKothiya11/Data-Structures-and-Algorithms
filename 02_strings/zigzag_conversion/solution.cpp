#include <string>
#include <vector>

class Solution {
public:
    std::string convert(const std::string& s, int numRows) {
        const int n = static_cast<int>(s.size());

        if (numRows <= 1 || numRows >= n) {
            return s;
        }

        std::vector<std::string> rows(numRows);
        int currentRow = 0;
        int direction = 1;

        for (const char ch : s) {
            rows[currentRow] += ch;

            if (currentRow == 0) {
                direction = 1;
            } else if (currentRow == numRows - 1) {
                direction = -1;
            }

            currentRow += direction;
        }

        std::string result;
        result.reserve(s.size());

        for (const std::string& row : rows) {
            result += row;
        }

        return result;
    }
};