# Count Inversions in an Array

## Problem Statement
Given an array of integers `arr`, find its **inversion count**. Two elements `arr[i]` and `arr[j]` form an inversion if `arr[i] > arr[j]` and `i < j`. 

The inversion count indicates how far (or close) the array is from being sorted. If the array is already sorted, the inversion count is `0`; if it is sorted in reverse order, the inversion count is maximal.

## Key Insight / Intuition
A brute force approach compares every pair, taking $O(n^2)$ time. To optimize this, we can adapt the **Merge Sort** algorithm, which naturally uses a divide-and-conquer strategy.

When we split the array into two halves, a valid inversion pair $(i, j)$ can fall into one of three categories:
1. Both elements are in the **left half**.
2. Both elements are in the **right half**.
3. One element is in the **left half** and the other is in the **right half** (cross-inversion).

By recursively sorting the halves, we can easily count the internal inversions. Crucially, because both sub-arrays become sorted during the process, we can count the cross-inversions in linear time during the **merge step**. If an element in the left sorted subarray is greater than an element in the right sorted subarray, then that left elemen-and **all remaining elements after it in the left subarray**-must also be greater than the right element.

## Approach

1. **Divide**: Find the midpoint `mid = left + (right - left) / 2` and recursively divide the array into left and right halves.
2. **Conquer**: 
   * Count inversions in the left half.
   * Count inversions in the right half.
3. **Combine & Count (Merge Step)**: Maintain two pointers, `leftIndex` pointing to the start of the left sorted half, and `rightIndex` pointing to the start of the right sorted half. 
   * If `arr[leftIndex] <= arr[rightIndex]`, no inversion is detected. Move `leftIndex` forward.
   * If `arr[leftIndex] > arr[rightIndex]`, an inversion is found. Since the left subarray is sorted, all elements from `leftIndex` up to `mid` are also greater than `arr[rightIndex]`. 
   * Add the count of these remaining elements, calculated as `(mid - leftIndex + 1)`, to our total inversions. Move `rightIndex` forward.
4. **Copy Back**: Merge the elements into a temporary array in sorted order, then copy them back into the original array.

## Mathematical Formulation
For a sorted left subarray $A$ and a sorted right subarray $B$:
If $A[i] > B[j]$, then for all indices $x$ such that $i \le x \le \text{mid}$:

$$A[x] > B[j]$$

The number of total inverted pairs added by $B[j]$ at that specific moment is:

$$\Delta \text{inversions} = \text{mid} - i + 1$$

## Complexity Analysis

* **Time Complexity:** $O(n \log n)$  
  The algorithm follows the exact recurrence relation of Merge Sort: $T(n) = 2T(n/2) + O(n)$. The array is divided into halves $\log n$ times, and the merging phase takes linear $O(n)$ time at each level of the recursion tree.
* **Space Complexity:** $O(n)$  
  An auxiliary buffer array `merged` of size up to $n$ is allocated during the merge step to hold elements temporarily in sorted order.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Nested Loops)** | $O(n^2)$ | $O(1)$ | Checks all pairs. Very simple but hits TLE (Time Limit Exceeded) for large inputs. |
| **Self-Balancing BST (e.g., AVL)** | $O(n \log n)$ | $O(n)$ | Inserts elements into a tree one by one and counts elements greater than the current item. High pointer overhead. |
| **Fenwick Tree / Segment Tree** | $O(n \log n)$ | $O(n)$ | Highly optimized for range queries. Performs a coordinate compression step followed by point updates. Efficient but mathematically intensive. |