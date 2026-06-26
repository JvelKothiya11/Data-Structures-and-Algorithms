# Reverse Pairs

## Problem Statement
Given an integer array `nums`, return the number of **reverse pairs** in the array. A reverse pair is a pair $(i, j)$ where:
* `0 <= i < j < nums.length`
* `nums[i] > 2 * nums[j]`

## Key Insight / Intuition
A brute-force approach checks every pair $(i, j)$ which takes $O(n^2)$ time. To design an optimal solution, we can adapt the divide-and-conquer strategy from **Merge Sort**. 

When dividing the array into a left sorted half and a right sorted half, a reverse pair can be found:
1. Entirely within the **left half**.
2. Entirely within the **right half**.
3. Splitting across both halves where index $i$ is in the left sub-array and index $j$ is in the right sub-array.

Because both sub-arrays are already independently sorted before they are merged, we can calculate the cross-half pairs efficiently. If `nums[leftIndex] > 2 * nums[rightIndex]`, then due to the sorted nature of the left sub-array, all elements from `leftIndex` to the end of the left partition (`mid`) will *also* be strictly greater than `2 * nums[rightIndex]`. 

Instead of resetting our pointers, we can use a **two-pointer linear scan** right before standard merging. The `rightIndex` pointer moves monotonically forward across iterations, allowing us to find pairs in $O(n)$ time per merge step.

## Approach

1. **Divide**: Split the array recursively into left and right halves using `mid = left + (right - left) / 2`.
2. **Conquer**: 
   * Recursively calculate reverse pairs within the left half.
   * Recursively calculate reverse pairs within the right half.
3. **Count Cross Pairs (`countReversePairs`)**: Before merging the two sorted halves, use a two-pointer approach to count pairs where elements split across borders:
   * Loop through each element `leftIndex` from `left` to `mid`.
   * Advance `rightIndex` from `mid + 1` to `right` as long as the condition `nums[leftIndex] > 2 * nums[rightIndex]` is met.
   * Since `rightIndex` only moves forward, the number of valid right elements matching the current left element is the total span advanced from the beginning of the right sub-array: `rightIndex - (mid + 1)`. Add this value to our rolling sum.
4. **Merge**: Combine the two halves back into sorted order using standard Merge Sort logic, then repeat up the recursion tree.

> **Type Casting Note**: The condition checks `values[leftIndex] > 2LL * values[rightIndex]`. The suffix `LL` forces the multiplication to take place using 64-bit signed integers (`long long`), safely preventing integer overflow scenarios when working with bounds close to `INT_MAX` or `INT_MIN`.

## Complexity Analysis

* **Time Complexity:** $O(n \log n)$  
  The recursion depth of the divide-and-conquer approach is bounded by $\log n$. At each level of the tree, the counting phase and the merge phase both execute sequentially in $O(n)$ linear time. This satisfies the classic recurrence relation $T(n) = 2T(n/2) + O(n)$.
* **Space Complexity:** $O(n)$  
  An auxiliary buffer vector `merged` is allocated at each recursion layer to execute the merge step, maxing out at size $n$.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Nested Loops)** | $O(n^2)$ | $O(1)$ | Checks all pairs sequentially. Fails with TLE (Time Limit Exceeded) for large test cases. |
| **Fenwick Tree / Binary Indexed Tree (BIT)** | $O(n \log n)$ | $O(n)$ | Involves coordinate compression and a reverse-order value mapping. Very fast, but more structurally intensive to maintain compared to standard sorting modifications. |