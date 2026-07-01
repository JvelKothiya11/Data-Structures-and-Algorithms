# N-Queens

## Problem Statement
The **n-queens** puzzle is the problem of placing `n` queens on an $n \times n$ chessboard such that no two queens attack each other.

A queen can attack another piece if it is in the same row, column, or diagonal. Given an integer `n`, return *all distinct solutions to the n-queens puzzle*. Each solution contains a distinct board configuration of the n-queens' placement, where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

---

## Key Insight / Intuition
The problem requires generating all valid configurations, making it a classic candidate for **Backtracking**. 

Instead of checking every cell on the board sequentially, we can exploit the rule that *every row must contain exactly one queen*. By placing queens row by row, we instantly eliminate row-based conflicts. To prevent column and diagonal conflicts efficiently without scanning the board at each step, we map out mathematical properties of a grid's diagonals:
* **Columns:** Tracked directly via column index (`column`).
* **Main Diagonals (Top-Right to Bottom-Left):** Summing the coordinates ($row + column$) yields a constant value for any cell on the same diagonal.
* **Anti-Diagonals (Top-Left to Bottom-Right):** Subtracting the coordinates ($row - column$) yields a constant value. We offset this by adding $n - 1$ to map it safely to positive array indices.

Using boolean lookup tracking arrays allows us to validate queen placement in constant $\mathcal{O}(1)$ time.

---

## Mathematical Derivation
For an $n \times n$ chessboard:
1. There are exactly $n$ columns, indexed from $0$ to $n-1$.
2. There are exactly $2n - 1$ unique main diagonals. The identifier formula is:
   $$\text{id}_{\text{main}} = \text{row} + \text{column}$$
   The range of this identifier is from $0$ to $2n - 2$.
3. There are exactly $2n - 1$ unique anti-diagonals. The identifier formula is normalized to avoid negative indices:
   $$\text{id}_{\text{anti}} = \text{row} - \text{column} + n - 1$$
   The range of this identifier is also from $0$ to $2n - 2$.

---

## Step-by-Step Approach
1. **State Initialization:** Create a blank $n \times n$ board representation (`std::vector<std::string>`). Initialize three boolean lookup vectors (`occupiedColumns`, `occupiedMainDiagonal`, `occupiedAntiDiagonal`) to track threats.
2. **Recursive Exploration (`placeQueens`):** Start the recursive function at `row = 0`.
3. **Base Case Recognition:** If `row == n`, a queen has been safely placed in every single row. Add the current board state copy to the global list of `solutions` and return.
4. **Iterative Placement (Pruning):** Loop through each `column` from $0$ to $n-1$ for the current row:
   - Compute diagonal identifiers using the mathematical derivations.
   - If the column, main diagonal, or anti-diagonal is already marked as occupied, the position is blocked; bypass it immediately.
5. **Backtracking Cycle:** If the position is safe:
   - Place the queen: Set `board[row][column] = 'Q'` and mark all respective lookups to `true`.
   - Move to the next level: Recurse into `row + 1`.
   - Reset (Backtrack): Revert `board[row][column] = '.'` and clear the lookup indexes back to `false` to evaluate subsequent branch states cleanly.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N!)$
  There are $N$ options for the first row, at most $N-2$ options for the second row, $N-4$ options for the next, and so on. As state-space pruning instantly eliminates invalid branches via $\mathcal{O}(1)$ vector lookups, the overall time bound behaves tightly according to the upper limit of the upper bound $\mathcal{O}(N!)$.

* **Space Complexity:** $\mathcal{O}(N^2)$
  The maximum recursion call stack depth scales linearly with the board size $\mathcal{O}(N)$. The state tracking vectors require $\mathcal{O}(N)$ memory space. The actual grid state size scales as $\mathcal{O}(N^2)$ to preserve the current intermediate board context during traversal.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Permutations** | $\mathcal{O}\binom{N^2}{N}$ | $\mathcal{O}(N^2)$ | Generates all possible combinations of placing $N$ items across $N^2$ boxes. Extremely redundant; completely impractical for $N > 4$. |
| **Naive Backtracking** | $\mathcal{O}(N! \cdot N)$ | $\mathcal{O}(N^2)$ | Places queens row by row but uses a helper validation function that loops through rows/diagonals every time to check safety, leading to a slower $\mathcal{O}(N)$ validation step. |