#include <vector>
#include <string>

class Solution {
private:
    void placeQueens(int row, int size, std::vector<std::string>& board, std::vector<std::vector<std::string>>& solutions, std::vector<bool>& occupiedColumns, std::vector<bool>& occupiedMainDiagonal, std::vector<bool>& occupiedAntiDiagonal) {
        if (row == size) {
            solutions.push_back(board);
            return;
        }

        for (int column = 0; column < size; ++column) {
            const int mainDiagonal = row + column;
            const int antiDiagonal = row - column + size - 1;
            const bool blocked = occupiedColumns[column] || occupiedMainDiagonal[mainDiagonal] || occupiedAntiDiagonal[antiDiagonal];

            if (blocked) {
                continue;
            }

            board[row][column] = 'Q';
            occupiedColumns[column] = true;
            occupiedMainDiagonal[mainDiagonal] = true;
            occupiedAntiDiagonal[antiDiagonal] = true;

            placeQueens(row + 1, size, board, solutions, occupiedColumns, occupiedMainDiagonal, occupiedAntiDiagonal);

            board[row][column] = '.';
            occupiedColumns[column] = false;
            occupiedMainDiagonal[mainDiagonal] = false;
            occupiedAntiDiagonal[antiDiagonal] = false;
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> solutions;
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<bool> occupiedColumns(n, false);
        std::vector<bool> occupiedMainDiagonal(2 * n - 1, false);
        std::vector<bool> occupiedAntiDiagonal(2 * n - 1, false);

        placeQueens(0, n, board, solutions, occupiedColumns, occupiedMainDiagonal, occupiedAntiDiagonal);
        return solutions;
    }
};