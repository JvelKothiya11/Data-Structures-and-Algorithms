#include <vector>

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        const int rowCount = static_cast<int>(matrix.size());
        const int colCount = static_cast<int>(matrix[0].size());

        int row = 0;
        int col = colCount - 1;

        while (row < rowCount && col >= 0) {
            const int current = matrix[row][col];

            if (current == target) {
                return true;
            }

            if (current > target) {
                --col;
            } else {
                ++row;
            }
        }

        return false;
    }
};