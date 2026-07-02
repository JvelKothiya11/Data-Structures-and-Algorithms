# Rotate Array

## Problem Statement
Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.

The rotation must be performed **in-place** with $\mathcal{O}(1)$ extra space.

---

## Key Insight / Intuition
A linear approach involving copying elements into a temporary array requires extra linear space. Shifting elements one by one $k$ times results in poor time complexity. 

The most elegant and optimal insight relies on **Array Reversal Symmetry**. 
When we rotate an array of size $N$ by $k$ steps, the trailing $k$ elements shift to the very front, and the remaining $N-k$ elements move to the back. We can achieve this precise distribution using three simple reversals:
1. Reverse the **entire array**. This moves the trailing $k$ elements to the front, but their relative order is inverted.
2. Reverse the **first $k$ elements** to restore their original relative ordering.
3. Reverse the **remaining $N-k$ elements** to fix their relative ordering as well.

---

## Step-by-Step Approach
1. **Handle Edge Cases:** Compute the effective rotation steps using `k %= size`. If the array is empty or the effective `k` is `0`, return immediately since no shift is needed.
2. **Global Reverse:** Flip the entire vector from beginning to end using `std::reverse(nums.begin(), nums.end())`.
3. **Prefix Reverse:** Restore the order of the newly positioned elements by reversing the first $k$ slots: `std::reverse(nums.begin(), nums.begin() + k)`.
4. **Suffix Reverse:** Restore the remainder of the array by reversing from index $k$ to the end: `std::reverse(nums.begin() + k, nums.end())`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm performs three reversal operations. The first passes through all $N$ elements, while the second and third process $k$ and $N-k$ elements respectively. In total, the elements are swapped exactly twice, resulting in a strictly linear execution time of $\mathcal{O}(2N) = \mathcal{O}(N)$.

* **Space Complexity:** $\mathcal{O}(1)$
  The reversals use standard in-place element swapping (`std::reverse`). No extra standard structures or memory allocations are configured, keeping auxiliary memory constant.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Shift by One)** | $\mathcal{O}(N \cdot k)$ | $\mathcal{O}(1)$ | Shifts elements right by 1 cell, repeated $k$ times. TLE risk if $k$ and $N$ are large. |
| **Extra Vector Buffer** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Places elements directly into their final slots in a new vector `(i + k) % N`, then copies back. Violates the in-place $\mathcal{O}(1)$ space constraint. |
| **Cyclic Replacements** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Moves elements to their target indices in cycles using GCD handling. Efficient but complex to write and error-prone during interviews. |