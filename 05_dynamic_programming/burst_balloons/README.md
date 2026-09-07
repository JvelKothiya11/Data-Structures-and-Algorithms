# Burst Balloons

## Problem Statement
You are given `n` balloons, indexed from `0` to `n - 1`. Each balloon is painted with a number on it represented by an array `nums`. You are asked to burst all the balloons.

If you burst the $i^{\text{th}}$ balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. If `i - 1` or `i + 1` goes out of bounds of the array, then treat it as if there is a balloon with a `1` painted on it.

Return *the maximum coins you can collect by bursting the balloons wisely*.

---

## Key Insight / Intuition
A naive divide-and-conquer strategy attempts to decide which balloon to burst **first**. However, bursting a balloon removes it and connects its left and right neighbors, creating dynamic subproblems whose boundaries constantly change based on prior choices.

The optimal insight flips the perspective: think about which balloon to burst **last** in a given range `(left, right)`.

If balloon `last` is the final balloon burst in the open interval `(left, right)`:
1. All balloons between `left` and `last` are already burst.
2. All balloons between `last` and `right` are already burst.
3. Therefore, the immediate neighbors remaining for balloon `last` are precisely `balloons[left]` and `balloons[right]`.

The coins collected from bursting `last` as the final balloon in this range are:

$$\text{coins} = \text{dp}[left][last] + \text{dp}[last][right] + \text{balloons}[left] \times \text{balloons}[last] \times \text{balloons}[right]$$

By defining subproblems around static boundaries, subproblems become completely independent, enabling **Bottom-Up Dynamic Programming**.

---

## Step-by-Step Approach
1. **Pad the Array:** Create an augmented array `balloons` of size $n + 2$, placing `1` at both boundaries (`balloons[0] = 1` and `balloons[n + 1] = 1`). Copy the original `nums` elements into indices `1` through `n`.
2. **DP Table Initialization:** Define a 2D table `dp` of size $(n + 2) \times (n + 2)$ initialized to `0`. `dp[left][right]` stores the maximum coins collected by bursting all balloons strictly between index `left` and index `right`.
3. **Iterate Range Boundaries:**
   - Iterate `left` boundary backwards from $n - 1$ down to $0$.
   - Iterate `right` boundary forwards from $left + 2$ up to $n + 1$.
4. **Choose the Last Balloon:** Loop through every possible balloon `last` strictly between `left` and `right` ($left < last < right$):
   - Calculate the total coins obtained if `last` is the final balloon burst in this sub-range.
   - Update `dp[left][right] = std::max(dp[left][right], coins)`.
5. **Return Result:** The answer for bursting all original balloons bounded by the artificial padding sits at `dp[0][n + 1]`.

---

## Complexity Analysis

Let $N$ be the number of balloons in the input array `nums`.

* **Time Complexity:** $\mathcal{O}(N^3)$
  There are three nested loops: `left` runs $\mathcal{O}(N)$ times, `right` runs $\mathcal{O}(N)$ times, and evaluating the optimal `last` split takes $\mathcal{O}(N)$ iterations. Total state transitions scale as $\mathcal{O}(N^3)$.

* **Space Complexity:** $\mathcal{O}(N^2)$
  Allocates a 2D matrix of size $(N + 2) \times (N + 2)$ for the DP table and an augmented vector of size $N + 2$.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Permutations** | $\mathcal{O}(N!)$ | $\mathcal{O}(N)$ | Evaluates all $N!$ orderings of bursting balloons. Infeasible for $N > 10$. |
| **Top-Down DP with Memoization** | $\mathcal{O}(N^3)$ | $\mathcal{O}(N^2)$ | Recursively evaluates ranges `(left, right)` and caches results. Intuitive, but incurs stack recursion overhead. |