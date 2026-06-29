# Peak Index in a Mountain Array

## Problem Statement
An array `arr` is a **mountain array** if it satisfies the following properties:
1. `arr.length >= 3`
2. There exists some index `i` ($0 < i < \text{arr.length} - 1$) such that:
   - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]` (strictly increasing)
   - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]` (strictly decreasing)

Given a mountain array `arr`, return the index `i` such that `arr[0] < arr[1] < ... < arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`.

The problem guarantees that the input array is a valid mountain array and requires a solution with better than linear time complexity.

---

## Key Insight / Intuition
The array can be visualized as two distinct monotonic parts: an **ascending slope** and a **descending slope** meeting at a single maximum peak. 

Because the data is logically ordered/partitioned, we do not need to check every element. We can apply **Binary Search**. At any midpoint index `mid`:
* If `arr[mid] < arr[mid + 1]`, we are currently on the **ascending slope**. The peak must lie strictly to the right of `mid`.
* If `arr[mid] > arr[mid + 1]`, we are on the **descending slope** (or at the peak itself). The peak must lie at `mid` or to its left.

By analyzing the local slope around `mid`, we can eliminate half of the search space at each iteration.

---

## Step-by-Step Approach
1. **Initialize Search Boundaries:** Set `left = 0` and `right = arr.size() - 1`.
2. **Binary Search Loop:** Run the loop while `left < right`.
3. **Calculate Midpoint:** Avoid integer overflow using:
   $$\text{mid} = \text{left} + \frac{\text{right} - \text{left}}{2}$$
4. **Evaluate Slope:** Check if `arr[mid] < arr[mid + 1]`.
   - **If true (Ascending):** The peak is further right. Narrow the search window by setting `left = mid + 1`.
   - **If false (Descending):** `mid` could be the peak, or the peak is to the left. Narrow the search window by setting `right = mid`.
5. **Convergence:** The loop terminates when `left == right`. This single remaining index points exactly to the mountain peak. Return `left`.

---

## Complexity Analysis

Let $N$ be the number of elements in the array `arr`.

* **Time Complexity:** $\mathcal{O}(\log N)$
  The search space is cut in half during every single comparison step. For an array of size $N$, the algorithm takes at most $\log_2(N)$ iterations to converge on the peak element.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm executes entirely in place using a few primitive integer pointers (`left`, `right`, `mid`), consuming constant auxiliary memory.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Linear Scan (Brute Force)** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Iterates from index 0 until `arr[i] > arr[i+1]`. Simple to write but fails to meet optimization constraints for large $N$. |
| **Standard Max Element Lookup** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Uses `std::max_element`. Searches the entire array blindly without exploiting the "mountain" structural property. |