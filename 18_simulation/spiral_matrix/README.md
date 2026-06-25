# Spiral Matrix

## Problem Statement
Given an $m \times n$ `matrix`, return all elements of the `matrix` in **spiral order** (clockwise starting from the top-left corner).

## Key Insight / Intuition
The problem requires traversing a 2D grid in concentric layers, moving clockwise from the outside inward. 

To achieve this without repeating elements or losing track of the trajectory, we can establish four boundaries: `top`, `bottom`, `left`, and `right`. As we complete a traversal of a side (e.g., traveling across the top row from left to right), that boundary shrinks inward (e.g., `top` increments down). We repeat this layer-by-layer cycle until the boundaries cross each other.

## Approach

1. **Setup Boundaries**: Initialize four pointers:
   * `top = 0` (first row)
   * `bottom = rowCount - 1` (last row)
   * `left = 0` (first column)
   * `right = colCount - 1` (last column)
2. **Layer Traversal Loop**: Loop while `top <= bottom` and `left <= right`:
   * **Traverse Left to Right**: Move along the `top` row from `left` to `right`. Once done, increment `top` to shift the boundary down.
   * **Traverse Top to Bottom**: Move down the `right` column from `top` to `bottom`. Once done, decrement `right` to shift the boundary left.
   * **Traverse Right to Left**: *Check if `top <= bottom` still holds.* If true, move across the `bottom` row from `right` to `left`. Once done, decrement `bottom` to shift the boundary up.
   * **Traverse Bottom to Top**: *Check if `left <= right` still holds.* If true, move up the `left` column from `bottom` to `top`. Once done, increment `left` to shift the boundary right.
3. **Termination**: When the boundary pointers cross or overlap invalidly, the loop ends, and the collected elements are returned.

> **Crucial Defensive Checks**: After shifting `top` and `right`, the boundaries change midway through the loop iteration. We must re-verify that `top <= bottom` and `left <= right` before performing the backward runs (Right-to-Left and Bottom-to-Top) to prevent duplicate processing in single-row or single-column matrices.

## Complexity Analysis

* **Time Complexity:** $O(m \times n)$  
  Every single element in the $m \times n$ matrix is visited exactly once during the outer layer iterations.
* **Space Complexity:** $O(1)$  
  The output list `spiral` is used to store results and does not count towards auxiliary space. Only a fixed number of pointer trackers are maintained.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Simulation via Direction Vectors** | $O(m \times n)$ | $O(m \times n)$ | Tracks coordinates $(r, c)$ and flips directions when encountering boundaries or a "visited" marker matrix. Intuitive but demands excessive memory to track state. |