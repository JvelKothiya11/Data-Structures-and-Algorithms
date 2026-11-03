# Minimum Moves to Equal Array Elements III

## Problem Statement
Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.

In one move, you can increment any single element of the array by `1`.

---

## Key Insight / Intuition
When the allowed operation permits incrementing *any individual element* by `1` per move, the target value to make all elements equal must be the **maximum element** currently present in the array. 

* Any target value smaller than the current maximum would be impossible to reach using only upward increments.
* To minimize the total number of increments, we bring every smaller element up to match the largest element.
* Therefore, the total moves required is simply the sum of the differences between the maximum element and each respective element in the array:

$$\text{Total Moves} = \sum_{i=0}^{n-1} (\text{largest} - \text{nums}[i]) = (n \times \text{largest}) - \text{totalSum}$$

---

## Step-by-Step Approach
1. **Edge Case Handling:** If the `nums` vector is empty, return `0` moves immediately.
2. **Find the Maximum Element:** Locate the largest value in the array using `std::max_element`.
3. **Accumulate Differences:** Loop through each element, compute `largest - value`, and accumulate it into `totalMoves`.
4. **Return Result:** Return the final accumulated move count.

---

## Complexity Analysis

Let $N$ be the number of elements in the `nums` array.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm performs a single pass to find the maximum element (`std::max_element`) and another linear pass to calculate the differences, resulting in linear time complexity.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm operates entirely in-place using constant auxiliary space for scalar trackers (`largest`, `totalMoves`).

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Simulation / Priority Queue** | $\mathcal{O}(N \log N)$ or worse | $\mathcal{O}(N)$ | Simulates increments explicitly or uses a heap. Unnecessary overhead compared to direct mathematical calculation. |