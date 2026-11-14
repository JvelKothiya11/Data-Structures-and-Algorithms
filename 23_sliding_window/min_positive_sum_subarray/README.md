# Min Positive Sum Subarray

## Problem Statement
Given an integer array `nums` and two integers `l` and `r`, find the minimum sum of a subarray whose length is between `l` and `r` (inclusive) and whose sum is **strictly positive** (i.e., greater than `0`). 

Return *the minimum positive sum of such a subarray*. If no such subarray exists, return `-1`.

---

## Key Insight / Intuition
Any subarray sum from index `left` to `right - 1` can be expressed efficiently using prefix sums as:

$$\text{Sum}(left, right) = \text{prefixSum}[right] - \text{prefixSum}[left]$$

The problem imposes two major constraints on the subarray length ($l \le \text{length} \le r$):
1. **Length Bounds:** The length constraint $l \le right - left \le r$ can be rearranged into bounds for the starting prefix index:

$$right - r \le left \le right - l$$
   
2. **Positive Sum Requirement:** We want $\text{prefixSum}[right] - \text{prefixSum}[left] > 0$, which implies:

$$\text{prefixSum}[left] < \text{prefixSum}[right]$$

To minimize a positive difference, we need to find a preceding prefix sum `prefixSum[left]` that is strictly less than `prefixSum[right]` but **as close to it as possible**. 

We can maintain this sliding window of valid prefix sums using a **`std::multiset`**:
* As `right` advances, we introduce new valid left-boundary prefix sums into our window.
* When the window exceeds length `r`, we remove expired prefix sums.
* For each `right`, we query the multiset using `lower_bound` to find the largest prefix sum smaller than `prefixSum[right]` in logarithmic time.

---

## Step-by-Step Approach
1. **Compute Prefix Sums:** Build a `prefixSum` vector of size $n + 1$ where `prefixSum[i]` stores the cumulative sum of elements from the beginning up to index `i - 1`.
2. **Initialize Trackers:** Set `minimumSum = LLONG_MAX` and create an empty `std::multiset<long long> prefixWindow`.
3. **Iterate Through Right Boundaries:** Loop `right` from `l` to `n`:
   - **Expand Window:** Insert the prefix sum corresponding to the shortest allowable subarray (`prefixSum[right - l]`) into `prefixWindow`.
   - **Query Closest Smaller Prefix:** Use `prefixWindow.lower_bound(prefixSum[right])`. Step back one position to locate the largest prefix sum strictly smaller than `prefixSum[right]`.
   - **Update Minimum Sum:** If a valid preceding prefix sum exists, compute the positive difference and update `minimumSum`.
   - **Shrink Window:** If `right >= r`, remove the expired prefix sum `prefixSum[right - r]` from `prefixWindow` to maintain the upper length constraint `r`.
4. **Return Result:** If `minimumSum` was updated, cast it to an integer and return it. Otherwise, return `-1`.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N \log N)$
  The algorithm iterates through the array of size $N$ once. In each iteration, multiset operations (`insert`, `lower_bound`, `find`, and `erase`) take logarithmic time $\mathcal{O}(\log N)$, resulting in an overall quasilinear time complexity.

* **Space Complexity:** $\mathcal{O}(N)$
  Requires auxiliary space for the prefix sum array of size $N + 1$ and the `std::multiset` storing up to $r - l + 1$ prefix values.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Subarray Enumeration** | $\mathcal{O}(N \times (r - l))$ or $\mathcal{O}(N^2)$ | $\mathcal{O}(1)$ | Checks every possible valid subarray length between `l` and `r`. Simple to implement, but inefficient for large arrays or wide length ranges. |