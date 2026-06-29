# Search in Rotated Sorted Array

## Problem Statement
There is an integer array `nums` sorted in ascending order (with **distinct** values). 

Prior to being passed to your function, `nums` is possibly **rotated** at an unknown pivot index `k` ($1 \le k < \text{nums.length}$) such that the resulting array becomes `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (0-indexed). For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index `3` and become `[4,5,6,7,0,1,2]`.

Given the array `nums` after the possible rotation and an integer `target`, return the *index of `target` if it is in `nums`, or `-1` if it is not in `nums`*.

You must write an algorithm with $\mathcal{O}(\log N)$ runtime complexity.

---

## Key Insight / Intuition
The problem dictates a logarithmic time complexity, which naturally points to **Binary Search**. However, because the array is rotated, it is no longer globally sorted. 

The core realization is that if you divide a rotated sorted array in half at *any* arbitrary midpoint `mid`, **at least one of the two halves will always remain strictly sorted**. 

By checking if the left boundary element is less than or equal to the midpoint element (`nums[left] <= nums[mid]`), we can instantly deduce which half is normally sorted. Once the sorted half is identified, we check if our `target` falls within its boundary ranges. If it does, we search that half; if it doesn't, we eliminate it and search the opposite (inflected) half.

---

## Step-by-Step Approach
1. **Initialize Pointers:** Set `left = 0` and `right = nums.size() - 1`.
2. **Binary Search Loop:** Run the loop while `left <= right`.
3. **Midpoint Assessment:** Calculate the midpoint index `mid`. If `nums[mid] == target`, immediately return `mid`.
4. **Identify Sorted Half:** Compare `nums[left]` with `nums[mid]`:
   - **Case A: Left Half is Sorted (`nums[left] <= nums[mid]`)**
     - Check if `target` lies within the sorted range: `nums[left] <= target < nums[mid]`.
     - If it does, shrink the search window to the left half (`right = mid - 1`).
     - Otherwise, the target must be in the right half (`left = mid + 1`).
   - **Case B: Right Half is Sorted (`nums[left] > nums[mid]`)**
     - Check if `target` lies within the sorted range: `nums[mid] < target <= nums[right]`.
     - If it does, shrink the search window to the right half (`left = mid + 1`).
     - Otherwise, the target must be in the left half (`right = mid - 1`).
5. **Target Not Found:** If the loop terminates without hitting the condition in step 3, return `-1`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(\log N)$
  At each decision juncture, the algorithm halves the search window by modifying either the `left` or `right` pointer based on standard range conditions. Even with the added rotation check, it retains the pure logarithmic properties of traditional Binary Search.

* **Space Complexity:** $\mathcal{O}(1)$
  The traversal relies solely on a fixed set of pointer trackers (`left`, `right`, `mid`) and local copies of array values, keeping memory consumption bounded and constant.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Linear Search** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Simple `for`-loop check. Fails interview constraints as it ignores the sorted architecture completely. |
| **Pivot-Find + Dual Binary Search** | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ | First finds the pivot index (minimum element), then executes a standard Binary Search on either the left or right sub-segment. Works well but requires writing two separate search functions. |