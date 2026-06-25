# Search a 2D Matrix II

## Problem Statement
Write an efficient algorithm that searches for a value `target` in an $m \times n$ integer matrix. This matrix has the following properties:
* Integers in each row are sorted in ascending from left to right.
* Integers in each column are sorted in ascending from top to bottom.

## Key Insight / Intuition
The naive approach is to look through the entire matrix, taking $O(m \times n)$ time. However, we can take advantage of the dual-sorting property by strategically picking a starting point that allows us to eliminate a row or a column at every step. 

If we start at the **top-right corner** (or the bottom-left corner), the position acts as a decision pointer:
* All elements to its **left** in the same row are **smaller**.
* All elements **below** it in the same column are **larger**.

This allows us to treat the matrix similarly to a Binary Search Tree (BST), pruning our search space in linear time.

## Approach

1. **Initialize Pointers**: Place a pointer at the top-right corner: `row = 0` and `col = colCount - 1`.
2. **Search Loop**: While `row` is within the grid bounds (`row < rowCount`) and `col` is valid (`col >= 0`):
   * **Case 1**: If `matrix[row][col] == target`, we have found the element. Return `true`.
   * **Case 2**: If `matrix[row][col] > target`, then every other element further down in the current column must also be larger than the target (since columns are sorted). We can safely eliminate this entire column by decrementing `col`.
   * **Case 3**: If `matrix[row][col] < target`, then every other element to the left in the current row must also be smaller than the target (since rows are sorted). We can safely eliminate this entire row by incrementing `row`.
3. **Termination**: If the pointers step completely out of the matrix boundaries without matching the target, return `false`.

## Complexity Analysis

* **Time Complexity:** $O(m + n)$  
  At each step of the loop, we either decrement the column index or increment the row index. In the absolute worst case (searching for a value that would be near the bottom-left corner), the algorithm will traverse at most $m$ rows and $n$ columns.
* **Space Complexity:** $O(1)$  
  The search space is pruned in-place using two scalar index variables (`row` and `col`), requiring zero auxiliary memory overhead.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Linear Scan)** | $O(m \times n)$ | $O(1)$ | Simple to write but ignores the sorted nature of the matrix entirely. Far too slow for large inputs. |
| **Row-by-Row Binary Search** | $O(m \log n)$ | $O(1)$ | Performs standard binary search on each of the $m$ rows. Better than brute force, but sub-optimal compared to a joint matrix traversal. |