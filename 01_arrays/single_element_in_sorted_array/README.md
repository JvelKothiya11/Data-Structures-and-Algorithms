# Single Element in a Sorted Array

## Problem Statement
You are given a sorted array consisting of integers where every element appears exactly twice, except for one element which appears exactly once.

Return *the single element that appears only once*.

Your solution must run in $\mathcal{O}(\log N)$ time and $\mathcal{O}(1)$ space.

---

## Key Insight / Intuition
Since the array is sorted and contains pairs alongside a single isolated element, the total size of the array will always be odd. 

The presence of the single element creates an index-alignment disruption:
* **Before the single element:** All valid pairs start at an **even index** and end at an **odd index** $(e.g., \text{index } 0 \text{ and } 1, 2 \text{ and } 3)$.
* **After the single element:** The pairs shift, meaning they now start at an **odd index** and end at an **even index** $(e.g., \text{index } 4 \text{ and } 5)$.

By leveraging a **Binary Search**, we can pick a midpoint, align it to its respective even-indexed pair start (`pairStart`), and check if `nums[pairStart] == nums[pairStart + 1]`. If they match, the disruption hasn't happened yet, so the single element lies to the right. If they don't match, the disruption already occurred, meaning the single element is at or to the left of `pairStart`.

---

## Step-by-Step Approach
1. **Initialize Boundaries:** Set `left = 0` and `right = nums.size() - 1`.
2. **Binary Search Loop:** Iterate while `left < right`.
3. **Locate the Pair Start:** Find the midpoint index and store it in `pairStart`. If `pairStart` is an odd index, decrement it by `1` so it points to the beginning of a normal even-indexed pair.
4. **Evaluate Symmetry:** Compare `nums[pairStart]` with its partner `nums[pairStart + 1]`:
   - **If they match (`validPair` is true):** The array layout is normal up to this point. The single element must exist deeper in the right half. Update `left = pairStart + 2`.
   - **If they do not match (`validPair` is false):** The pair alignment is broken, indicating the single element was passed. The single element could be `pairStart` itself or located further left. Update `right = pairStart`.
5. **Convergence:** When `left == right`, the pointers converge directly on the unique element. Return `nums[left]`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(\log N)$
  The algorithm halves the effective search window on every iteration by identifying which side of the single-element disruption the midpoint lands on. This adheres strictly to the logarithmic boundary required by the problem.

* **Space Complexity:** $\mathcal{O}(1)$
  The search updates integer positions entirely in place, using a constant amount of auxiliary memory.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Linear Scan** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Compares adjacent pairs step-by-step. Simple but too slow to pass the logarithmic constraint. |
| **Bit Manipulation (XOR)** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | XORs all numbers together; duplicate pairs cancel out to $0$, leaving the single element. Elegant, works on unsorted arrays, but is still linear. |