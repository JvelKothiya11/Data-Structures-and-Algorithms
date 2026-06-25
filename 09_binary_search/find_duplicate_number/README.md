# Find the Duplicate Number

## Problem Statement
Given an array of integers `nums` containing $n + 1$ integers where each integer is in the range $[1, n]$ inclusive. There is only **one repeated number** in `nums`, return this repeated number.

You must solve the problem **without** modifying the array `nums` and use only $O(1)$ extra space.

## Key Insight / Intuition
This problem can be mapped directly to a **Linked List Cycle Detection** problem. 

Because the array contains $n + 1$ elements with values ranging strictly from $1$ to $n$, we can treat each value as a pointer targeting a next index (i.e., `index -> nums[index]`). Since index `0` will never be jumped to (as values only start at 1), it acts as a perfect entry point. 

Because there is a duplicate number, multiple indices will point to the same value (index). This convergence creates a loop or cycle in our traversal path. Finding the duplicate number is equivalent to finding the **entrance of the cycle** using **Floyd's Tortoise and Hare (Cycle Detection) Algorithm**.

## Approach

The algorithm operates in two main phases:

1. **Phase 1 (Detect Intersection)**: 
   * Initialize two pointers, `slowPointer` and `fastPointer`, at the starting position `nums[0]`.
   * Move `slowPointer` by one step (`slow = nums[slow]`) and `fastPointer` by two steps (`fast = nums[nums[fast]]`).
   * They are guaranteed to eventually meet at an intersection point inside the cycle.
2. **Phase 2 (Find Cycle Entrance)**:
   * Keep `slowPointer` at the intersection point, and reset a new pointer `cycleStart` back to the beginning of the array (`nums[0]`).
   * Move both pointers forward at the exact same pace of one step at a time.
   * The point where they meet again is the exact entrance to the cycle, which corresponds to the duplicate number.

## Mathematical Derivation
Let:
* $F$ = Distance from the start of the array to the entrance of the cycle.
* $C$ = Length of the cycle.
* $a$ = Distance from the cycle entrance to the phase 1 intersection point.

When the two pointers meet in Phase 1:
* Distance traveled by Tortoise (slow): $D_{slow} = F + a$
* Distance traveled by Hare (fast): $D_{fast} = F + a + k \cdot C$ (where $k$ is the number of full loops around the cycle)

Since the Hare travels exactly twice as fast as the Tortoise:
$$D_{fast} = 2 \cdot D_{slow}$$
$$F + a + k \cdot C = 2(F + a)$$
$$F + a = k \cdot C \implies F = k \cdot C - a$$

This equation ($F = k \cdot C - a$) tells us that the distance from the array start to the cycle entrance ($F$) is mathematically equivalent to traveling the remaining distance of the cycle loop from the intersection point ($k \cdot C - a$). Thus, by stepping both pointers at equal speed in Phase 2, they will meet perfectly at the entrance.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Phase 1 and Phase 2 both scale linearly with the size of the array. The pointers will loop at most a few times before converging, ensuring linear runtime.
* **Space Complexity:** $O(1)$  
  The algorithm tracks positions using only scalar pointer variables, running entirely in-place without copying or allocating new memory blocks.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Modifies Input? | Pros / Cons |
| :--- | :--- | :--- | :--- | :--- |
| **Brute Force (Nested Loops)** | $O(n^2)$ | $O(1)$ | No | Compares every pair. Too slow for large inputs. |
| **Sorting** | $O(n \log n)$ | $O(1)$ or $O(n)$ | **Yes** | Elements align next to duplicates. Violates the read-only constraint. |
| **Hash Map / Set / Visited Array** | $O(n)$ | $O(n)$ | No | Tracks frequencies. Violates constant space constraint. |
| **Negative Marking** | $O(n)$ | $O(1)$ | **Yes** | Flips `nums[abs(val)]` to negative to flag seen elements. Violates read-only constraint. |