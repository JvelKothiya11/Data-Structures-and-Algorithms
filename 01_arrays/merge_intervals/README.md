# Merge Intervals

## Problem Statement
Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

## Key Insight / Intuition
If the intervals are sorted by their start times, any intervals that can be merged will be adjacent to each other in the sorted list. 

Once sorted, we can process intervals sequentially. For any two consecutive intervals, they overlap if the start time of the current interval is less than or equal to the end time of the previously processed interval. If they overlap, we can merge them by extending the end time of the previous interval to the maximum end time found between the two.

## Approach

1. **Sort**: Sort the input `intervals` array based on the starting values of each interval. This guarantees that if `intervals[i]` overlaps with any prior interval, it must overlap with the most recently merged interval.
2. **Initialize**: Create an empty list/vector `mergedIntervals` to store the result.
3. **Iterate**: Loop through each `interval` in the sorted list:
   * **Case 1 (No Overlap)**: If `mergedIntervals` is empty, or if the start of the current `interval` is strictly greater than the end of the last interval in `mergedIntervals`, there is no overlap. Push the current `interval` directly into `mergedIntervals`.
   * **Case 2 (Overlap)**: Otherwise, an overlap exists. Update the end time of the last interval in `mergedIntervals` to be the maximum of its current end time and the end time of the current `interval`.
4. **Return**: Return `mergedIntervals`.

## Mathematical Formulation / Overlap Condition
Let the last merged interval be $I_{prev} = [S_{prev}, E_{prev}]$ and the current interval being evaluated be $I_{curr} = [S_{curr}, E_{curr}]$.

Because the array is sorted, we know that $S_{prev} \le S_{curr}$. 

An overlap occurs if and only if:
$$S_{curr} \le E_{prev}$$

When this condition is true, the merged interval becomes:
$$I_{new} = [S_{prev}, \max(E_{prev}, E_{curr})]$$

## Complexity Analysis

* **Time Complexity:** $O(n \log n)$  
  Sorting the array of $n$ intervals dominates the execution time, taking $O(n \log n)$ time. The subsequent linear scan through the sorted intervals takes $O(n)$ time. Thus, the overall time complexity is $O(n \log n)$.
* **Space Complexity:** $O(\log n)$ or $O(n)$  
  The space complexity depends entirely on the implementation of the sorting algorithm (e.g., `std::sort` typically uses $O(\log n)$ auxiliary stack space for QuickSort/IntroSort). The output array `mergedIntervals` is required by the problem statement and does not count towards auxiliary space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Graph Component)** | $O(n^2)$ | $O(n^2)$ | Model intervals as nodes in a graph and add edges between overlapping intervals. Find connected components. Very complex and inefficient. |
| **Sorting Start & End Separately** | $O(n \log n)$ | $O(n)$ | Extract all starts and ends into separate arrays, sort them independently, and use two pointers to reconstruct intervals. Works perfectly but requires extra space. |