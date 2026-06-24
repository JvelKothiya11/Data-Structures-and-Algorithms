# Set Matrix Zeroes

## Problem Statement
Given an $m \times n$ integer matrix, if an element is `0`, set its entire row and column to `0`. The modification must be done **in-place**.

## Key Insight / Intuition
A naive solution requires extra arrays to keep track of which rows and columns need to be zeroed out. To achieve $O(1)$ space, we can reuse the **first row** and the **first column** of the matrix itself as our state-tracking arrays. 

If any element `matrix[row][col]` is `0`, we flag its row by setting `matrix[row][0] = 0` and its column by setting `matrix[0][col] = 0`. Because the first row and first column overlap at `matrix[0][0]`, we handle their individual zeroing states using two independent boolean flags (`shouldClearFirstRow` and `shouldClearFirstColumn`) to avoid data contamination.

## Approach

1. **Scan First Row & Column**: Check if the first row contains any `0` and set `shouldClearFirstRow` to `true`. Check if the first column contains any `0` and set `shouldClearFirstColumn` to `true`.
2. **Flag Inner Matrix**: Iterate through the rest of the matrix (from `row = 1` and `col = 1`). If `matrix[row][col] == 0`, store this information by setting the header cells `matrix[row][0] = 0` and `matrix[0][col] = 0`.
3. **Update Inner Matrix**: Iterate through the inner matrix again. If its corresponding row header or column header is `0`, update `matrix[row][col] = 0`.
4. **Update First Row & Column**: Finally, check our initial flags. If `shouldClearFirstRow` is true, set the entire first row to `0`. If `shouldClearFirstColumn` is true, set the entire first column to `0`.

## Complexity Analysis

* **Time Complexity:** $O(m \times n)$  
  The algorithm scans the matrix a fixed number of times (constant passes). For a matrix of dimensions $m \times n$, this results in quadratic time proportional to the total number of cells.
* **Space Complexity:** $O(1)$  
  By utilizing the matrix's own header cells for tracking state, the auxiliary memory overhead is restricted solely to two boolean variables.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Dummy Values)** | $O((m \times n) \cdot (m + n))$ | $O(1)$ | Changes cells to a placeholder symbol (like `-1000000`) when a zero is found, then makes a second pass. Risk of tracking collisions if placeholder exists naturally in input. |
| **Auxiliary Arrays / Sets** | $O(m \times n)$ | $O(m + n)$ | Highly intuitive. Uses two arrays/hash sets to track the indices of rows and columns to be zeroed. Requires extra space. |