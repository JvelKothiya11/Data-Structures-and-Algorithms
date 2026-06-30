# Median of Two Sorted Arrays

## Problem Statement
Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return the **median** of the two sorted arrays.

The overall run time complexity should be $\mathcal{O}(\log(m+n))$.

---

## Key Insight / Intuition
The naive approach is to merge the two sorted arrays into one, which takes linear time $\mathcal{O}(m+n)$. To achieve a logarithmic runtime, we must avoid merging altogether.

The core insight is to view the problem as finding a valid **partition** across both arrays. If we split both arrays into a left half and a right half such that:
1. The total number of elements in the combined left halves equals the total number of elements in the combined right halves (or has one extra element for odd totals).
2. Every element in the combined left halves is less than or equal to every element in the combined right halves.

Since both arrays are already sorted, we only need to ensure that the cross-boundary conditions hold:
* The largest element on the left side of array 1 (`leftMax1`) must be $\le$ the smallest element on the right side of array 2 (`rightMin2`).
* The largest element on the left side of array 2 (`leftMax2`) must be $\le$ the smallest element on the right side of array 1 (`rightMin1`).

We can use **Binary Search** on the *smaller* array to dynamically find this correct partition point.

---

## Step-by-Step Approach
1. **Ensure Array 1 is Smaller:** If `nums1` is larger than `nums2`, swap them by recursively calling the function with arguments reversed. This guarantees the binary search runs on the smaller array, minimizing the search space.
2. **Initialize Search Space:** Set `left = 0` and `right = size1` (bounds of the smaller array `nums1`).
3. **Partition Estimation:** Inside the binary search loop:
   - Compute `partition1` as the midpoint of the current search range in `nums1`.
   - Derivation for `partition2`: Since the left partition must hold half of the total elements, it is defined as:

$$\text{partition2} = \frac{\text{size1} + \text{size2} + 1}{2} - \text{partition1}$$

4. **Boundary Checks (Edge Cases):** Extract boundary values `leftMax1`, `rightMin1`, `leftMax2`, and `rightMin2`. If a partition falls outside the array bounds, simulate it using $-\infty$ (`INT_MIN`) for left markers or $+\infty$ (`INT_MAX`) for right markers.
5. **Verify Partition Validity:**
   - **Perfect Partition:** If `leftMax1 <= rightMin2` and `leftMax2 <= rightMin1`, the cut is valid. 
     - If the combined size is *even*, the median is the average of the maximum left element and minimum right element.
     - If the combined size is *odd*, the median is simply the maximum of the left elements.
   - **Too Far Right:** If `leftMax1 > rightMin2`, the partition in `nums1` is too far right. Move the binary search left (`right = partition1 - 1`).
   - **Too Far Left:** Otherwise, the partition in `nums1` is too far left. Move the binary search right (`left = partition1 + 1`).

---

## Complexity Analysis

Let $M$ be the size of `nums1` and $N$ be the size of `nums2`.

* **Time Complexity:** $\mathcal{O}(\log(\min(M, N)))$
  By enforcing that the binary search is always performed on the shorter array, the search space is bounded by $\min(M, N)$. Each step cuts this search space in half, yielding logarithmic performance.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm tracks partition indices using a few primitive integer pointers in place. No dynamic memory or recursive data structures are allocated, fulfilling the constant space requirement.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Merge and Sort** | $\mathcal{O}((M+N) \log(M+N))$ | $\mathcal{O}(M+N)$ | Combine both arrays completely and sort. Extremely inefficient. |
| **Two-Pointer Merge** | $\mathcal{O}(M+N)$ | $\mathcal{O}(1)$ | Uses a merge-step from merge sort with two pointers to count up to the median index. Does not meet the logarithmic constraint. |