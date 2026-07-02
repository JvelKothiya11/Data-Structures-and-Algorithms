# Remove Duplicates from Sorted Array II

## Problem Statement
Given an integer array `nums` sorted in non-decreasing order, remove some duplicates **in-place** such that each unique element appears **at most twice**. The relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result.

Return `k` after placing the final result in the first `k` slots of `nums`.

Do not allocate extra space for another array. You must do this by modifying the input array in-place with $\mathcal{O}(1)$ extra memory.

---

## Key Insight / Intuition
The array is already sorted, which guarantees that all duplicate numbers sit adjacent to one another. 

Since any element can appear at most twice, we can use a **Two-Pointer/Read-Write approach**. We maintain a `writeIndex` pointer that outlines the boundary of our valid processed array. 
For every incoming element (`value`) during our scan:
* The first two elements of the array are always valid because a number can safely repeat up to twice.
* For any subsequent element, it is only allowed into our valid zone if it is **not equal** to the element sitting two positions behind our write boundary (`nums[writeIndex - 2]`). If it matches, it means allowing this element would create a triplet of duplicates, so we skip it.

---

## Step-by-Step Approach
1. **Initialize Boundary Pointer:** Establish a `writeIndex` set to `0` to keep track of where the next allowed element should be placed.
2. **Scan the Array:** Use a fast-running loop to iterate through every `value` in the input `nums` vector.
3. **Apply the At-Most-Two Rule:** For each `value`, check two logical safety gates:
   - If `writeIndex < 2`, the element falls into the initial safe zone.
   - If `nums[writeIndex - 2] != value`, the current element does not match the element placed two positions back, meaning the duplicate threshold has not been exceeded.
4. **Overwrite & Increment:** If either condition passes, write the element to `nums[writeIndex]` and increment `writeIndex`. If both fail, simply do nothing (ignore the element and move on).
5. **Return Valid Length:** Once the iteration finishes, `writeIndex` will point to the index immediately following the last valid element, representing the total count `k` of the valid array.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm utilizes a single loop that traverses the array from the first element to the last exactly once. Each item undergoes constant time checks $\mathcal{O}(1)$, yielding a strictly linear time execution.

* **Space Complexity:** $\mathcal{O}(1)$
  No extra arrays or dynamic allocations are used. Modifications are written directly over the original storage cells using only one primitive tracking variable (`writeIndex`), adhering to the constant space constraint.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Extra Array)** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Counts frequencies and builds a secondary array before overwriting back. Simple but completely violates the in-place space requirements. |
| **Element Shifting (`std::vector::erase`)** | $\mathcal{O}(N^2)$ | $\mathcal{O}(1)$ | Scans elements and calls `.erase()` whenever a triplet is spotted. Erasing inside an array triggers trailing element shifts, dropping efficiency to quadratic time. |