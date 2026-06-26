# Trapping Rain Water

## Problem Statement
Given $n$ non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

## Key Insight / Intuition
The amount of water that can be trapped on top of any single bar at index $i$ depends entirely on the blocking walls around it. Specifically, it is bounded by the **minimum** of the tallest bar to its left and the tallest bar to its right. 

Instead of precomputing these boundary heights using extra arrays, we can use a **Two-Pointer** approach. By placing pointers at both ends of the array (`left` and `right`) and maintaining running variables for the maximum heights seen from each side (`leftMax` and `rightMax`), we can determine water storage safely. Whichever side has a smaller bounding wall dictates the water level, allowing us to process that specific index immediately and step inward.

## Approach

1. **Initialize**: Set up two tracking pointers, `left = 0` and `right = height.size() - 1`. Initialize `leftMax = 0`, `rightMax = 0`, and `trappedWater = 0`.
2. **Two-Pointer Loop**: While `left < right`:
   * Update `leftMax` with the maximum of itself and `height[left]`.
   * Update `rightMax` with the maximum of itself and `height[right]`.
   * **Compare Max Bounds**:
     * If `leftMax <= rightMax`: The water capacity at the `left` pointer is bottlenecked by `leftMax`. Add `leftMax - height[left]` to `trappedWater`, then move `left` one step forward (`++left`).
     * If `leftMax > rightMax`: The water capacity at the `right` pointer is bottlenecked by `rightMax`. Add `rightMax - height[right]` to `trappedWater`, then move `right` one step backward (`--right`).
3. **Return**: Once the pointers meet, return the accumulated `trappedWater`.

## Mathematical Formulation
For any column $i$, the trapped water height $W[i]$ is calculated as:

$$W[i] = \max(0, \min(\text{leftMax}[i], \text{rightMax}[i]) - \text{height}[i])$$

By leveraging the two-pointer condition `leftMax <= rightMax`, we guarantee that even if there is an unknown taller wall far to the right, it is at least as tall as `leftMax`. Thus, $\min(\text{leftMax}, \text{rightMax})$ simplifies safely to `leftMax` for the current `left` index.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  The two pointers move toward each other, inspecting each element of the array exactly once. This guarantees a single-pass linear time complexity.
* **Space Complexity:** $O(1)$  
  The solution relies entirely on a few state variables (`left`, `right`, `leftMax`, `rightMax`), requiring zero auxiliary heap allocation.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $O(n^2)$ | $O(1)$ | Scans the left and right halves completely for every single element. Scales terribly. |
| **Dynamic Programming (Precomputed Max Arrays)** | $O(n)$ | $O(n)$ | Precomputes two arrays (`leftMax` and `rightMax`) in separate passes. Highly readable but requires linear space. |
| **Monotonic Stack** | $O(n)$ | $O(n)$ | Keeps track of bars in a decreasing stack structure. Computes water horizontally in blocks rather than vertically per column. Intuitive but relies on dynamic space allocations. |