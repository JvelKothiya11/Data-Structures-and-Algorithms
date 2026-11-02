# Minimum Moves to Equal Array Elements II

## Problem Statement
Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.

In one move, you can increment or decrement an element of the array by `1`.

---

## Key Insight / Intuition
This problem can be modeled mathematically as finding a value $k$ (the target number that all elements will become) that minimizes the sum of absolute deviations:

$$\text{Total Moves} = \sum_{i=0}^{n-1} |\text{nums}[i] - k|$$

According to the L1 norm minimization property (or the median theorem), the sum of absolute differences from a point $k$ is strictly minimized when $k$ is chosen to be the **median** of the dataset. 

* If $k$ is chosen as the mean, it minimizes the sum of *squared* differences (variance/L2 norm).
* To minimize *absolute* differences, the **median** is the optimal choice. 
* Sorting the array allows us to locate this median instantly at index `n / 2`.

---

## Step-by-Step Approach
1. **Edge Case Handling:** If the `nums` vector is empty, return `0` moves immediately.
2. **Sort the Array:** Sort `nums` in non-decreasing order using `std::sort`.
3. **Find the Median:** Identify the median element located at the middle index: `const int median = nums[n / 2];`.
4. **Accumulate Absolute Deviations:** Iterate through each element in the sorted array, calculate its absolute difference from the median using `std::abs`, and sum them up.
5. **Return Result:** Return the total accumulated moves.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N \log N)$
  The dominant operation is sorting the array, which takes $\mathcal{O}(N \log N)$ time. The subsequent linear pass to compute absolute differences runs in $\mathcal{O}(N)$ time.

* **Space Complexity:** $\mathcal{O}(1)$ or $\mathcal{O}(\log N)$
  The algorithm modifies the vector in-place. The auxiliary space depends on the sorting implementation's stack recursion depth (typically $\mathcal{O}(\log N)$ for introsort).

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Quickselect Algorithm** | $\mathcal{O}(N)$ average | $\mathcal{O}(1)$ | Finds the median in expected linear time without fully sorting the array. Optimal in theory, but with higher implementation complexity and worst-case $\mathcal{O}(N^2)$ behavior unless randomized. |