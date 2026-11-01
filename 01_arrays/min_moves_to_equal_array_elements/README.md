# Minimum Moves to Equal Array Elements

## Problem Statement
Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.

In one move, you can increment `n - 1` elements of the array by `1`.

---

## Key Insight / Intuition
At first glance, simulating the process by incrementing $n - 1$ elements seems to imply we should target the maximum element or try to raise everything up. However, looking at the problem from a **relative perspective** reveals a powerful mathematical simplification:

* Incrementing $n - 1$ elements by $1$ is **mathematically equivalent to decrementing a single element by $1$** relative to all other elements.
* Our goal is to make all elements equal. Instead of trying to grow every element up to meet a rising maximum (which can cause overflow or complex adjustments), we can view the task as reducing every element down to the **minimum element** in the array.
* Therefore, the total number of moves required is simply the sum of the differences between each element and the minimum element:
  $$\text{Total Moves} = \sum_{i=0}^{n-1} (\text{nums}[i] - \text{minValue}) = \text{totalSum} - (n \times \text{minValue})$$

---

## Step-by-Step Approach
1. **Edge Case Handling:** If the `nums` vector is empty, return `0` moves immediately.
2. **Find the Minimum Element:** Locate the smallest value in the array using `std::min_element`.
3. **Calculate Total Sum:** Compute the sum of all elements in the array using `std::accumulate`.
4. **Compute Moves:** Subtract the product of the array size and `minValue` from `totalSum`, and return the result.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm performs two linear passes over the array: one to find the minimum element (`std::min_element`) and one to calculate the sum (`std::accumulate`). Both operations run in linear time.

* **Space Complexity:** $\mathcal{O}(1)$
  The calculations are performed entirely in-place using constant auxiliary space for accumulators and iterators.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Simulation / Brute Force** | $\mathcal{O}(N^2 \log N)$ or worse | $\mathcal{O}(1)$ | Repeatedly finds the min/max and increments $N - 1$ elements until all are equal. Highly inefficient and prone to Time Limit Exceeded (TLE). |
| **Sorting Approach** | $\mathcal{O}(N \log N)$ | $\mathcal{O}(\log N)$ | Sorts the array and sums differences from the first element. Simple, but slower due to sorting overhead. |