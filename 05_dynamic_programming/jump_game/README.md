# Jump Game

## Problem Statement
You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in the array represents your maximum jump length at that position.

Return `true` *if you can reach the last index, or `false` otherwise*.

---

## Key Insight / Intuition
This problem can be elegantly solved using a **Greedy Algorithm** by tracking the maximum reachable index at any point.

Instead of trying every possible jump combination (which leads to redundant path exploration), we simply maintain a running boundary called `farthestReachable`. As we step through the array from left to right:
* If we ever reach an `index` that is strictly greater than `farthestReachable`, it means we have stepped into a dead zone that is impossible to arrive at from any previous platform.
* At each accessible step, we dynamically update our reach capacity. If our `farthestReachable` boundary meets or exceeds the last index of the array, we can safely conclude that the end is attainable.

---

## Step-by-Step Approach
1. **Initialize Reach Tracker:** Declare `farthestReachable` and set it to `0` (since we start at the first index).
2. **Scan the Array:** Iterate through the array using an `index` pointer from `0` to `size - 1`.
3. **Check Accessibility:** At the start of each iteration, check if `index > farthestReachable`. If true, break and return `false` immediately because this index is unreachable.
4. **Greedily Update Horizon:** Calculate the maximum distance we could jump from the current tile ($index + nums[index]$) and update our boundary:

$$\text{farthestReachable} = \max(\text{farthestReachable}, \text{index} + \text{nums}[\text{index}])$$

5. **Early Termination:** Check if `farthestReachable` is greater than or equal to `size - 1`. If it is, return `true` early without scanning the remainder of the array.
6. **Fallback Return:** If the loop terminates naturally, return `true`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `nums`.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm performs a single, sequential pass over the array. Each iteration carries out constant time $\mathcal{O}(1)$ operations (basic comparisons and max updates), achieving linear runtime.

* **Space Complexity:** $\mathcal{O}(1)$
  No auxiliary data structures, arrays, or recursion blocks are allocated. The calculation updates a single primitive integer variable (`farthestReachable`) in place, keeping memory utilization entirely constant.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Backtracking (Brute Force)** | $\mathcal{O}(2^N)$ | $\mathcal{O}(N)$ | Exhaustively simulates every single jump choice. Results in TLE for arrays larger than a few dozen elements. |
| **Dynamic Programming (Top-Down/Bottom-Up)** | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | Stores whether an index can reach the end in a memoization table. Avoids repeating work but incurs quadratic time and linear space. |