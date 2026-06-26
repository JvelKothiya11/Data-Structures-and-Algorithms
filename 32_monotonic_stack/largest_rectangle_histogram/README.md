# Largest Rectangle in Histogram

## Problem Statement
Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, find the area of the largest rectangle in the histogram.

## Key Insight / Intuition
A brute-force approach considers every pair of bars as boundaries and finds the minimum height between them, leading to an $O(n^2)$ solution. To optimize this to linear time, we can use a **Monotonic Stack**.

The maximum rectangle using a particular bar as its height is bounded to the left and right by the first bars that are strictly *shorter* than it. By maintaining indices of the bars in the stack in **strictly increasing order of their heights**, we can defer calculating the area until we encounter a bar that is shorter than the bar at the top of the stack. This shorter bar acts as the right boundary, while the element below the top of the stack acts as the left boundary.

## Approach

1. **Monotonic Stack Initialization**: Create an empty `std::stack<int> indices` to store the positions of the bars.
2. **Iterate with a Dummy Guard**: Loop from `index = 0` up to `size` (inclusive). When `index == size`, treat the current height as a dummy value of `0`. This forces the algorithm to flush out and process all remaining bars inside the stack at the end of the array.
3. **Process Boundaries**: For each bar:
   * While the stack is not empty and the current bar's height is strictly less than the height of the bar at the stack's top:
     * Pop the top index from the stack—this bar's height will be the `height` of our target rectangle.
     * Calculate the `width`:
       * If the stack is empty after popping, it means the popped bar was the shortest bar seen so far, so it can extend all the way back to index `0`. The width is simply `index`.
       * Otherwise, the current top of the stack is the left boundary. The width is calculated as `index - indices.top() - 1`.
     * Update `maximumArea` with the calculated area (`height * width`).
   * Push the current `index` onto the stack.
4. **Return**: Return `maximumArea`.

## Mathematical Formulation
For a bar popped from the stack at index $t$ with height $H_t$:
* Let $R = \text{current index}$ (the right smaller boundary index).
* Let $L = \text{indices.top()}$ after popping $t$ (the left smaller boundary index).

The area contribution is given by:

$$\text{Area} = H_t \times (R - L - 1)$$

If no elements remain in the stack after popping $t$, the left boundary extends implicitly to the beginning of the histogram ($L = -1$), simplifying the formulation to:

$$\text{Area} = H_t \times R$$

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Every index from `0` to `size` is pushed onto the stack exactly once. Inside the nested `while` loop, each index is popped from the stack at most once. This ensures an amortized time complexity of $O(1)$ per bar, creating a total linear runtime of $O(n)$.
* **Space Complexity:** $O(n)$  
  In the worst-case scenario (e.g., the input heights are sorted in strictly ascending order), no elements will be popped during the main traversal, and the stack will store up to $n$ indices.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (All Pairs)** | $O(n^2)$ | $O(1)$ | Checks every possible sub-array to find the minimum height. Hits TLE (Time Limit Exceeded) for large constraints. |
| **Precomputed Smaller Boundaries** | $O(n)$ | $O(n)$ | Precomputes two arrays (`lessThanLeft` and `lessThanRight`) using a monotonic stack pattern in separate passes, then computes the max area in a final pass. Highly intuitive but uses multiple arrays. |