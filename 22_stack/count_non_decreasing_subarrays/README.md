# Count Non-Decreasing Subarrays

## Problem Statement
Given an integer array `nums` and an integer `k`, return *the number of subarrays that can be made non-decreasing with at most `k` operations*.

In one operation, you may increment or modify elements, or the problem asks for the count of subarrays that can form a non-decreasing sequence within a given cost budget `k`.

---

## Key Insight / Intuition
Finding the number of valid subarrays where a cost condition holds often lends itself to a **Two-Pointer / Sliding Window** approach. However, checking every subarray independently is too slow.

By traversing the array backwards from right to left, we can maintain a **Monotonic Deque** that tracks value blocks and their frequencies:
1. **Monotonic Stack/Deque Property:** When processing element `nums[left]`, we maintain a non-increasing sequence of values in our deque. If an incoming value is greater than preceding values in the deque, we merge them (accounting for the frequency of elements being raised) and accumulate the required `operations`.
2. **Cost Budget Management (`k`):** As the window expands, if the accumulated `operations` exceed `k`, we shrink the window from the right (`right` pointer moving backwards) by shedding elements from the front of our deque until the cost budget is satisfied.
3. **Subarray Counting:** For any valid `left` boundary, all endpoints from `left` up to `right` form valid non-decreasing subarrays, contributing `right - left + 1` to the total count.

---

## Step-by-Step Approach
1. **Initialize Trackers:** 
   - `monotonicDeque`: Stores pairs of `{value, frequency}` to manage collapsed ranges efficiently.
   - `operations = 0` and `validSubarrays = 0`: Accumulators for cost and valid subarray counts.
   - `right = n - 1`: The right boundary of our sliding window.
2. **Backward Iteration:** Loop `left` from $n - 1$ down to $0$:
   - **Merge Smaller Values:** While the deque is not empty and the back element's value is less than `nums[left]`, pop it, calculate the operation cost required to raise those elements to `nums[left]` multiplied by their frequency, and aggregate them into a combined `count`.
   - **Push to Deque:** Push `(nums[left], count)` into `monotonicDeque`.
   - **Contract Window:** While `operations > k`, reduce the operation cost by removing the contribution of the leftmost element, decrement its frequency, pop from the front if frequency hits zero, and decrement `right`.
3. **Accumulate Subarrays:** Add the valid window span `right - left + 1` to `validSubarrays`.
4. **Return Result:** Return the final accumulated `validSubarrays` count.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N)$
  Each element is pushed into and popped from the monotonic deque at most once across the entire traversal, resulting in an optimal linear time complexity.

* **Space Complexity:** $\mathcal{O}(N)$
  In the worst-case scenario (e.g., a strictly decreasing array), the deque can store up to $N$ unique value-frequency pairs.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Subarray Check** | $\mathcal{O}(N^3)$ or $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | Evaluates every possible subarray range and checks operation costs. Will heavily exceed time limits for large inputs. |