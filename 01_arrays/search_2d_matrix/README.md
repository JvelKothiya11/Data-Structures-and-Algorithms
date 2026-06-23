# Search a 2D Matrix

## Problem Statement
Write an efficient algorithm that searches for a value `target` in an $m \times n$ integer matrix. This matrix has the following properties:
* Integers in each row are sorted from left to right.
* The first integer of each row is greater than the last integer of the previous row.

Given these constraints, determine if `target` exists within the matrix in $\mathcal{O}(\log(m \times n))$ time.

---

## Key Insight / Intuition
The core insight is that the entire sorted 2D matrix can be treated as a single, contiguous **1D sorted array** of length $m \times n$. 

Because the rows are sequentially sorted and wrapped perfectly (the start of row $i$ is greater than the end of row $i-1$), we do not need to perform complex nested searches. Instead, we can apply standard **Binary Search** across a virtual 1D range spanning from index `0` to `(m * n) - 1`. 

The only modification needed is mapping our virtual 1D index `mid` back to its actual 2D coordinates `(row, col)` using basic modular arithmetic.

---

## Mathematical Derivation (Coordinate Mapping)
To translate a 1D index `mid` into a 2D matrix coordinate `(row, col)` where each row contains `n` columns, we use the following formulas:

1. **Row Index Calculation:**
   $$\text{row} = \lfloor \text{mid} / n \rfloor$$
   *Explanation:* Dividing the 1D index by the number of elements per row (`n`) tells us how many full rows have been skipped.

2. **Column Index Calculation:**
   $$\text{col} = \text{mid} \pmod n$$
   *Explanation:* The remainder represents the offset or column position within the current row.

### Concrete Example
Given a $3 \times 4$ matrix ($m = 3, n = 4$):
* Virtual 1D range: `0` to `11`.
* Let `mid = 6`.
* $\text{row} = 6 / 4 = 1$
* $\text{col} = 6 \pmod 4 = 2$
* Virtual index `6` maps directly to matrix element `matrix[1][2]`.

---

## Step-by-Step Approach
1. **Extract Matrix Dimensions:** Determine the number of rows `m` and columns `n`.
2. **Define Search Boundaries:** Set up binary search pointers:
   * `left = 0`
   * `right = (m * n) - 1`
3. **Execute Binary Search:** While `left <= right`:
   * Calculate the 1D midpoint: `mid = left + (right - left) / 2` (prevents integer overflow).
   * Map `mid` to 2D coordinates to extract the value: `value = matrix[mid / n][mid % n]`.
   * **Case 1:** If `value == target`, return `true`.
   * **Case 2:** If `value < target`, the target must be in the right half. Shift the boundary: `left = mid + 1`.
   * **Case 3:** If `value > target`, the target must be in the left half. Shift the boundary: `right = mid - 1`.
4. **Target Not Found:** If the loop terminates without a match, return `false`.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(\log(m \times n))$
The search space of size $m \times n$ is halved during every iteration of the binary search loop, matching the classic logarithmic pattern.

### Space Complexity: $\mathcal{O}(1)$
The algorithm searches the matrix completely in-place, tracking only a few structural primitive variables (`left`, `right`, `mid`, `value`) without allocating dynamic memory structures.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force Linear Search** | Scan every single cell row by row, column by column. | $\mathcal{O}(m \times n)$ | $\mathcal{O}(1)$ |
| **Row-by-Row Binary Search** | Loop through all $m$ rows and perform a separate binary search on each row of size $n$. | $\mathcal{O}(m \log n)$ | $\mathcal{O}(1)$ |
| **Staircase Search (Top-Right / Bottom-Left)** | Start at the top-right corner. If `current > target`, move left; if `current < target`, move down. | $\mathcal{O}(m + n)$ | $\mathcal{O}(1)$ |