# Sort Colors

## Problem Statement
Given an array `nums` with $n$ objects colored red, white, or blue, sort them **in-place** so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We use the integers `0`, `1`, and `2` to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function and in a single pass.

---

## Key Insight / Intuition
The problem is a classic variation of the **Dutch National Flag Algorithm** designed by Edsger Dijkstra. 

Instead of tracking counts or sorting traditionally, we can partition the array into three distinct zones using three pointers (`low`, `mid`, and `high`):
* All elements before `low` are `0`s (Red).
* All elements from `low` up to (but not including) `mid` are `1`s (White).
* All elements after `high` are `2`s (Blue).
* The elements from `mid` to `high` are unexamined.

By iterating through the array with `mid`, we continuously inspect elements and swap them into their correct segments, shrinking the unexamined window until `mid` passes `high`.

---

## Step-by-Step Approach
1. **Initialize Three Pointers:**
   * `low = 0`: Marks the boundary where the next `0` should be placed.
   * `mid = 0`: Acts as the active iterator evaluating the current element.
   * `high = nums.size() - 1`: Marks the boundary where the next `2` should be placed.
2. **Process Elements (Three-Way Partitioning):**
   While `mid <= high`, evaluate `nums[mid]`:
   * **Case 0 (`nums[mid] == 0`):** Swap `nums[low]` and `nums[mid]`. Since the element swapped from `low` to `mid` is guaranteed to be a `1` (or it is `mid` itself), we can safely increment both `low++` and `mid++`.
   * **Case 1 (`nums[mid] == 1`):** The element is already in the correct middle region. Simply advance the active pointer: `mid++`.
   * **Case 2 (`nums[mid] == 2`):** Swap `nums[mid]` and `nums[high]`. Decrement `high--`. Do *not* increment `mid` here because the new element swapped from `high` into `mid` is unexamined and needs to be evaluated in the next iteration.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n)$
The algorithm processes the array in a single pass. In every single step, either `mid` increments or `high` decrements, steadily reducing the unexamined portion of the array until the loop terminates.

### Space Complexity: $\mathcal{O}(1)$
The sorting is executed completely in-place. No auxiliary arrays or structures are used; only three integer pointers are tracked.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Counting Sort (Two-Pass)** | Scan the array once to count the frequencies of `0`s, `1`s, and `2`s. Scan a second time to overwrite the array sequentially using those counts. | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| **Standard Sorting** | Use a traditional comparison sort algorithm like Quick Sort or Merge Sort. | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ to $\mathcal{O}(n)$ |