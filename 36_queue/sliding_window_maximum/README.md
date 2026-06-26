# Sliding Window Maximum

## Problem Statement
Given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return an array containing the max element inside the sliding window at each step.

## Key Insight / Intuition
A brute-force approach finds the maximum element in each window by scanning all `k` elements, resulting in $O(n \cdot k)$ time. To optimize this to linear time, we need a data structure that allows us to find the maximum in $O(1)$ while tracking elements inside the dynamic window. 

This can be achieved using a **Monotonic Deque (Double-Ended Queue)**. We store the *indices* of elements in the deque such that their corresponding values are always in **strictly decreasing order**. 

When a new element arrives:
1. Any older element in the deque that is smaller than the incoming element will never get a chance to be the maximum of any future window. Thus, we can safely discard them from the back of the deque.
2. The largest element for the current window will naturally always reside at the `front` of the deque.

## Approach

1. **Initialize**: Create a `std::deque<int> window` to store array indices, and a `maximums` vector to collect results.
2. **Iterate Through Array**: For each index `index` in `nums`:
   * **Evict Out-of-Bound Indices**: Check if the index at the front of the deque has fallen out of the sliding window boundary (`window.front() <= index - k`). If so, remove it via `pop_front()`.
   * **Maintain Monotonicity**: Pop elements from the back of the deque (`pop_back()`) as long as they are smaller than or equal to the incoming element `nums[index]`.
   * **Insert**: Push the current `index` to the back of the deque.
   * **Record Result**: Once our iteration index reaches at least `k - 1`, the sliding window is fully formed. The current window's maximum value is retrieved in $O(1)$ time using `nums[window.front()]`.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Even though there are nested `while` loops inside the main loop, each element index is pushed into the deque exactly once and popped out at most once over the entire course of execution. This results in an amortized $O(1)$ processing time per element, yielding a total linear time complexity of $O(n)$.
* **Space Complexity:** $O(k)$  
  The deque stores at most $k$ elements at any given point (the maximum size of a single sliding window frame). The space required for the output array `maximums` is required by the problem and does not count toward auxiliary space complexity.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Nested Scans)** | $O(n \cdot k)$ | $O(1)$ | Scans all elements inside the window at every shift. Hits TLE (Time Limit Exceeded) for large constraints. |
| **Max-Heap / Priority Queue** | $O(n \log n)$ or $O(n \log k)$ | $O(n)$ or $O(k)$ | Stores elements in a max-heap. Gives immediate access to the max element, but removing out-of-bound entries that aren't at the top requires lazy deletion or customized heap mutations. |
| **Self-Balancing BST (`std::multiset`)** | $O(n \log k)$ | $O(k)$ | Maintains sorted order inside a tree. Allows simple structural insertion and deletion, but suffers from $\log k$ tree rebalancing overhead. |