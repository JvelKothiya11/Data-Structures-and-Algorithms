# Merge Sorted Array

## Problem Statement
You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

Merge `nums1` and `nums2` into a single array sorted in non-decreasing order. 

The redistribution must happen **in-place** inside the array `nums1`. To accommodate this, `nums1` has a length of $m + n$, where the first $m$ elements denote the elements that should be merged, and the last $n$ elements are set to `0` and should be ignored.

---

## Key Insight / Intuition
A naive approach would fill `nums1` from the front, but that requires shifting elements to the right to make room, leading to a suboptimal time complexity. 

The key insight is to **merge from the back to the front**. Since the last $n$ slots of `nums1` are initially empty placeholders ("buffers"), we can safely compare the largest elements of both arrays (found at their respective ends) and place the maximum directly into the highest available index at the back of `nums1`. This avoids overwriting any valid data in `nums1` and eliminates the need for extra memory or costly element shifts.

---

## Step-by-Step Approach
1. **Initialize Three Pointers:**
   * `i`: Points to the last valid element in `nums1` (index $m - 1$).
   * `j`: Points to the last element in `nums2` (index $n - 1$).
   * `k`: Points to the absolute last index of the combined array `nums1` (index $m + n - 1$).
2. **Compare and Place (Backwards Loop):**
   * While both `i` and `j` are valid ($\ge 0$):
     * Compare `nums1[i]` and `nums2[j]`.
     * Place the larger of the two at `nums1[k]`.
     * Decrement the pointer used (`i` or `j`) and move the target pointer `k` one step backward.
3. **Handle Remaining Elements:**
   * If `j >= 0` after the loop, it means there are still smaller elements left in `nums2` that need to be copied over to the front of `nums1`.
   * If `i >= 0` first, no action is needed because those elements are already in their correct sorted positions at the front of `nums1`.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(m + n)$
In the worst-case scenario, we iterate through all elements of both arrays exactly once to place them into their correct positions.

### Space Complexity: $\mathcal{O}(1)$
The merge is executed completely in-place within the pre-allocated buffer of `nums1`, using only a few pointer variables. No auxiliary arrays are created.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Naively Append & Sort** | Copy elements of `nums2` into the tail end of `nums1`, then call `std::sort()` on the entire array. | $\mathcal{O}((m + n) \log (m + n))$ | $\mathcal{O}(1)$ or $\mathcal{O}(m+n)$ depending on sort |
| **Two Pointers (Forward)** | Create a new auxiliary array of size $m$. Copy `nums1`'s valid elements into it, then use two pointers to merge from the front into `nums1`. | $\mathcal{O}(m + n)$ | $\mathcal{O}(m)$ |