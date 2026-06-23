# 3Sum

## Problem Statement
Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

The solution set must not contain duplicate triplets.

---

## Key Insight / Intuition
A naive brute-force approach checks every single triplet combinatorially, leading to an inefficient $\mathcal{O}(n^3)$ runtime. 

By sorting the array first, we can optimize this problem significantly. Sorting enables us to fix one element (`nums[i]`) and transform the remaining problem into a classic **Two Sum II (Sorted)** problem for the rest of the array. Using a two-pointer approach within the sorted window allows us to find matching pairs efficiently. 

Furthermore, sorting makes duplicate elimination trivial: if the current element is identical to the previous one at any pointer level, we can simply skip it to guarantee that our final output list contains only unique triplets.

---

## Step-by-Step Approach
1. **Sort the Array:** Sort `nums` in non-decreasing order. This setup allows the use of two-pointer directionality based on numerical values.
2. **Fix the First Element (`i`):** Iterate through the array with a loop index `i` representing our first element in the triplet.
   * **Skip Duplicates:** If `nums[i] == nums[i-1]`, skip the iteration to avoid duplicate triplets starting with the same value.
3. **Two-Pointer Search (`left` and `right`):** For each fixed `i`, initialize `left = i + 1` and `right = n - 1`. 
   * Compute the sum: `sum = nums[i] + nums[left] + nums[right]`.
   * **Case 1: `sum == 0`**
     * A valid triplet is found! Add `{nums[i], nums[left], nums[right]}` to the results.
     * Move both `left` forward and `right` backward.
     * Continuously increment `left` and decrement `right` as long as they point to values identical to their respective previous positions to bypass duplicates.
   * **Case 2: `sum < 0`**
     * The total value is too small. Since the array is sorted, increment `left` to increase the overall sum.
   * **Case 3: `sum > 0`**
     * The total value is too large. Decrement `right` to reduce the overall sum.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n^2)$
Sorting the array takes $\mathcal{O}(n \log n)$ time. The nested loops pair a linear outer loop with a linear two-pointer inner scan ($$\mathcal{O}(n \times n) = \mathcal{O}(n^2)$$). The $\mathcal{O}(n^2)$ operation dominates the overall runtime.

### Space Complexity: $\mathcal{O}(1)$ or $\mathcal{O}(n)$
The algorithm operates directly on the input array using pointers. The actual auxiliary space complexity depends on the implementation details of `std::sort` (typically $\mathcal{O}(\log n)$ stack space for Quick Sort/Introsort variants).

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force** | Use three nested loops to check every combination of elements. | $\mathcal{O}(n^3)$ | $\mathcal{O}(1)$ |
| **Hash Map / Set** | Fix one element, then use a hash set to perform a 2Sum check on the remaining elements. Needs a separate hash set structure to handle final triplet uniqueness. | $\mathcal{O}(n^2)$ | $\mathcal{O}(n)$ |