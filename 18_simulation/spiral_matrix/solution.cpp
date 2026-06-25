#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        const int rowCount = static_cast<int>(matrix.size());
        const int colCount = static_cast<int>(matrix[0].size());

        std::vector<int> spiral;
        spiral.reserve(rowCount * colCount);

        int top = 0;
        int bottom = rowCount - 1;
        int left = 0;
        int right = colCount - 1;

        while (top <= bottom && left <= right) {
            for (int col = left; col <= right; ++col) {
                spiral.push_back(matrix[top][col]);
            }
            ++top;

            for (int row = top; row <= bottom; ++row) {
                spiral.push_back(matrix[row][right]);
            }
            --right;

            if (top <= bottom) {
                for (int col = right; col >= left; --col) {
                    spiral.push_back(matrix[bottom][col]);
                }
                --bottom;
            }

            if (left <= right) {
                for (int row = bottom; row >= top; --row) {
                    spiral.push_back(matrix[row][left]);
                }
                ++left;
            }
        }

        return spiral;
    }
};