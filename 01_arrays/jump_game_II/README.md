# Jump Game II

## Problem Statement
You are given a 0-indexed array of integers `nums` of length `n`. You are initially positioned at `nums[0]`.

Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at index `i`, you can jump to any `nums[i] + j` where:
* $0 \le j \le \text{nums}[i]$ and
* $i + j < n$

Return *the minimum number of jumps specified to reach `nums[n - 1]`*. The test cases are generated such that you can always reach the last index.

---

## Key Insight / Intuition
This problem can be conceptualized as finding the shortest path using a **Greedy Breadth-First Search (BFS)**, layered within a single linear traversal.

Instead of deciding which specific index to jump to next, we map out "levels" or "windows" of reachable intervals. We maintain two boundaries:
* `farthestReachable`: The ultimate index we can reach from *any* of the indices within our current window.
* `currentRangeEnd`: The outer boundary of our current jump's reach.

As we iterate through the array, we continually push out our `farthestReachable` horizon. When our scanning index catches up to `currentRangeEnd`, it means we have completely explored all possible launchpads within the current jump range. We are forced to make another jump, and we update `currentRangeEnd` to our newly discovered maximum horizon (`farthestReachable`).

---

## Step-by-Step Approach
1. **Initialize Game Variables:** - `jumpCount = 0`: Tracks the minimum number of jumps taken.
   - `currentRangeEnd = 0`: Marks the maximum index reachable using the current number of jumps.
   - `farthestReachable = 0`: Tracks the absolute furthest index reachable from any visited index so far.
2. **Loop Over Window Bounds:** Loop from `index = 0` up to `size - 2` (we stop right before the final element because once we hit or bypass it, no further jump scheduling is needed).
3. **Greedily Update Horizon:** For every index visited, evaluate how far it can take you ($index + nums[index]$) and cache the max possible reach inside `farthestReachable`:

$$\text{farthestReachable} = \max(\text{farthestReachable}, \text{index} + \text{nums}[\text{index}])$$

4. **Transition Windows (Trigger Jump):** If `index == currentRangeEnd`:
   - Increment `jumpCount` by 1.
   - Shift the `currentRangeEnd` boundary forward to point to `farthestReachable`.
5. **Return Result:** Once the loop completes, return `jumpCount`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm implements a single pass from the beginning of the array up to $N-2$. Inside the loop, it performs constant time operations $\mathcal{O}(1)$ consisting of maximum evaluations and point comparisons. This yields a linear execution window.

* **Space Complexity:** $\mathcal{O}(1)$
  All allocations happen completely in-place. The solution maintains the optimization profile by storing only a few primitive integer trackers (`jumpCount`, `currentRangeEnd`, `farthestReachable`), keeping auxiliary memory usage entirely flat.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Dynamic Programming (Min Steps array)** | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | Builds a table where `dp[i]` stores the min jumps to reach index `i`. Incurs quadratic time overhead due to inner loop updates. |
| **Pure BFS Structure** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Implemented using an explicit queue to compute intervals. Conceptually identical to the greedy strategy but introduces space allocation for structural wrappers. |