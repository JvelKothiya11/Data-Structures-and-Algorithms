#include <vector>

class Solution {
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        const int rowCount = static_cast<int>(matrix.size());
        const int colCount = static_cast<int>(matrix[0].size());

        bool shouldClearFirstRow = false;
        bool shouldClearFirstColumn = false;

        for (int col = 0; col < colCount; ++col) {
            if (matrix[0][col] == 0) {
                shouldClearFirstRow = true;
                break;
            }
        }

        for (int row = 0; row < rowCount; ++row) {
            if (matrix[row][0] == 0) {
                shouldClearFirstColumn = true;
                break;
            }
        }

        for (int row = 1; row < rowCount; ++row) {
            for (int col = 1; col < colCount; ++col) {
                if (matrix[row][col] == 0) {
                    matrix[row][0] = 0;
                    matrix[0][col] = 0;
                }
            }
        }

        for (int row = 1; row < rowCount; ++row) {
            for (int col = 1; col < colCount; ++col) {
                if (matrix[row][0] == 0 || matrix[0][col] == 0) {
                    matrix[row][col] = 0;
                }
            }
        }

        if (shouldClearFirstRow) {
            for (int col = 0; col < colCount; ++col) {
                matrix[0][col] = 0;
            }
        }
        
        if (shouldClearFirstColumn) {
            for (int row = 0; row < rowCount; ++row) {
                matrix[row][0] = 0;
            }
        }
    }
};