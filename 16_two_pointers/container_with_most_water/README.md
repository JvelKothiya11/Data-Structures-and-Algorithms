# Container With Most Water

## Problem Statement
Given $n$ non-negative integers $height[0], height[1], \dots, height[n-1]$, where each represents a point at coordinate $(i, height[i])$. $n$ vertical lines are drawn such that the two endpoints of the line $i$ are at $(i, height[i])$ and $(i, 0)$.

Find two lines that, together with the x-axis, form a container such that the container contains the most water. Return the maximum amount of water a container can store.

> **Note:** You may not slant the container.

---

## Key Insight / Intuition
The volume of water is constrained by two factors: **width** (the horizontal distance between the lines) and **height** (the shorter of the two vertical lines). 

$$Area = \min(\text{height}[left], \text{height}[right]) \times (right - left)$$

A brute-force solution checks every single pair, but we can optimize this drastically using a **Two-Pointer Approach**. By starting with the maximum possible width (pointers at the absolute left and right ends), any subsequent movement of a pointer will naturally decrease the width. 

To offset this guaranteed loss in width, our only hope of finding a larger area is to look for a larger height. Therefore, at each step, we should greedily discard the shorter line and move its pointer inward, as keeping it can never yield a larger container with a smaller width.

---

## Step-by-Step Approach
1. **Initialize Two Pointers:** Place the `left` pointer at index `0` and the `right` pointer at the last index (`height.size() - 1`).
2. **Track Maximum Capacity:** Maintain a variable `maxWater` initialized to `0`.
3. **Scan Inward:** While `left < right`:
   * **Calculate Current Height:** Find the limiting boundary height: `h = min(height[left], height[right])`.
   * **Calculate Current Width:** Compute the distance between boundaries: `width = right - left`.
   * **Update Maximum:** Calculate the current area (`h * width`) and update `maxWater` if it exceeds the previous maximum.
   * **Greedy Shift:** Compare the heights at both pointers. Increment `left` if the left boundary is shorter; otherwise, decrement `right`.
4. **Return Result:** Once the pointers meet, return the accumulated `maxWater`.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n)$
The algorithm uses a single pass over the array. In each iteration of the loop, the distance between the two pointers decreases by exactly 1, meaning the loop runs a maximum of $n$ times.

### Space Complexity: $\mathcal{O}(1)$
The solution runs entirely in-place, creating only a few primitive variable allocations (`left`, `right`, `h`, `width`, `maxWater`) independent of the input size.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force** | Use nested loops to calculate the area for every possible pair of lines and track the maximum. | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |