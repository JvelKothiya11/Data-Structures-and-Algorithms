# Minimum Size Subarray Sum

## Problem Statement
Given an array of positive integers `nums` and a positive integer `target`, return *the **minimal length** of a contiguous subarray of which the sum is greater than or equal to `target`*. If there is no such subarray, return `0` instead.

---

## Key Insight / Intuition
Because all elements in the input array are positive integers, the cumulative sum of any subarray is strictly monotonic: expanding the window increases the sum, and shrinking the window decreases it. 

This monotonicity makes the problem an ideal candidate for a **Sliding Window (Two-Pointer) Approach**:
* We maintain a dynamic window defined by a `left` and `right` pointer.
* We expand the window to the right by adding elements to our `windowSum`.
* The moment `windowSum` satisfies our condition (`windowSum >= target`), we record the window's length, and then greedily shrink the window from the left (`++left`) to find the smallest possible valid length while maintaining the condition.

---

## Step-by-Step Approach
1. **Initialize State Trackers:**
   - `left = 0`: The starting boundary of the sliding window.
   - `windowSum = 0`: Tracks the sum of elements currently inside the window.
   - `minLength = INT_MAX`: Stores the minimum valid subarray length found so far.
2. **Expand the Window (`right` pointer):** Loop through indices `right` from `0` to `n - 1`:
   - Add `nums[right]` to `windowSum`.
3. **Contract the Window (`left` pointer):** While `windowSum >= target`:
   - Update `minLength` with the current window size: `right - left + 1`.
   - Shrink the window by subtracting `nums[left]` from `windowSum` and incrementing `left`.
4. **Return Result:** After the loop completes, check if `minLength` was updated. If it remains `INT_MAX`, no valid subarray exists; return `0`. Otherwise, return `minLength`.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N)$
  Although there is a `while` loop nested inside the `for` loop, each element is visited at most twice: once when expanded by the `right` pointer and once when contracted by the `left` pointer. Thus, the total operations scale linearly.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm operates entirely in-place using a few scalar variables (`left`, `windowSum`, `minLength`), requiring constant auxiliary memory.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (All Subarrays)** | $\mathcal{O}(N^2)$ | $\mathcal{O}(1)$ | Tests every possible starting and ending index. Inefficient and will exceed time limits for large inputs. |
| **Prefix Sums + Binary Search** | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | Computes prefix sums and uses `std::lower_bound` to find the matching range for each index. Useful if negative numbers are allowed with certain constraints, but slower than the sliding window. |