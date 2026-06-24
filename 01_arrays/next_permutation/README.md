# Next Permutation

## Problem Statement
Implement **next permutation**, which rearranges numbers into the lexicographically next greater permutation of numbers. If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order). 

The replacement must be **in-place** and use only constant extra memory.

## Key Insight / Intuition
A sequence that is strictly decreasing has no lexicographically greater permutation (e.g., `[3, 2, 1]`). To find the next greater permutation, we must find the rightmost element that breaks this decreasing order. This element is called the **pivot**. 

By replacing the pivot with the next largest element to its right (its **successor**) and then reversing the sequence following the pivot into ascending order, we achieve the smallest possible increment to the overall sequence value.

## Approach

1. **Find the Break Point (Pivot)**: Traverse the array from right to left to find the first element `nums[pivotIndex]` that is smaller than its subsequent element `nums[pivotIndex + 1]`.
2. **Find the Successor**: If a valid pivot is found (i.e., the array is not entirely in descending order), traverse from right to left again to find the first element `nums[successorIndex]` that is strictly greater than `nums[pivotIndex]`.
3. **Swap**: Swap the elements at `pivotIndex` and `successorIndex`.
4. **Reverse the Tail**: Reverse the subarray starting right after `pivotIndex` to the end of the array. This changes a descending suffix into an ascending suffix, minimizing its lexicographical value.

> **Special Case**: If no pivot is found (`pivotIndex < 0`), the entire array is sorted in descending order. Reversing the whole array transforms it into the lowest possible order (ascending).

## Algorithmic Visualization

Consider the array `[1, 2, 7, 4, 3, 1]`:
* **Step 1**: Moving left, `2` is the first element smaller than its neighbor `7`. **Pivot = 2** (index 1).
* **Step 2**: Moving left from the end, `3` is the first element greater than `2`. **Successor = 3** (index 4).
* **Step 3**: Swap pivot and successor $\rightarrow$ `[1, 3, 7, 4, 2, 1]`.
* **Step 4**: Reverse everything after index 1 $\rightarrow$ `[1, 3, 1, 2, 4, 7]`.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  In the worst case, the algorithm scans the array at most two times (to find the pivot and the successor) and reverses a portion of the array. All these operations take linear time proportional to the array size $n$.
* **Space Complexity:** $O(1)$  
  The modifications are performed entirely in-place using a few index pointers, utilizing no extra memory.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Generate All)** | $O(n! \cdot n)$ | $O(n!)$ | Generates all possible permutations, sorts them, and finds the next one. Unusable for $n > 10$. |

> **Note:** The applied implementation mirrors the approach used by the C++ built-in utility `std::next_permutation`.