# 4Sum

## Problem Statement
Given an array `nums` of $n$ integers and an integer `target`, return an array of all the **unique quadruplets** `[nums[a], nums[b], nums[c], nums[d]]` such that:
* `0 <= a, b, c, d < n`
* `a`, `b`, `c`, and `d` are **distinct** indices.
* `nums[a] + nums[b] + nums[c] + nums[d] == target`

The solution set must not contain duplicate quadruplets.

---

## Key Insight / Intuition
The 4Sum problem extends the 3Sum pattern by adding another layer of nesting. A brute-force solution using four nested loops runs in $\mathcal{O}(n^4)$ time, which is highly inefficient.

By **sorting the array**, we can break down the problem structurally. Sorting allows us to fix the first two numbers (`nums[i]` and `nums[j]`) using two nested loops, reducing the core task to finding the remaining two numbers via a **Two-Pointer Approach** within the sorted window. 

### Overcoming Integer Overflow
Summing four standard 32-bit integers can easily exceed the limits of a signed integer (`INT_MAX` or `INT_MIN`) if the inputs are large. To counter this, we upcast the arithmetic calculation by multiplying the first term by `1LL`, evaluating the cumulative sum as a 64-bit signed integer (`long long`).

---

## Step-by-Step Approach
1. **Sort the Array:** Sort `nums` in non-decreasing order to facilitate duplicate skipping and two-pointer tracking.
2. **Fix First Element (`i`):** Loop from `0` to `n - 4`. 
   * *Duplicate Check:* If `i > 0` and `nums[i] == nums[i - 1]`, skip to prevent matching identical combinations.
3. **Fix Second Element (`j`):** Loop from `i + 1` to `n - 3`.
   * *Duplicate Check:* If `j > i + 1` and `nums[j] == nums[j - 1]`, skip to maintain uniqueness.
4. **Two-Pointer Search (`left` & `right`):** Initialize `left = j + 1` and `right = n - 1`. 
   * Calculate `sum = nums[i] + nums[j] + nums[left] + nums[right]` using `1LL` casting.
   * **Case 1: `sum == target`**
     * Capture the unique quadruplet `{nums[i], nums[j], nums[left], nums[right]}`.
     * Move both pointers inward (`++left`, `--right`).
     * Use inline loops to skip any consecutive duplicate values for both `left` and `right`.
   * **Case 2: `sum < target`**
     * The total sum is too low. Move `left` forward to tap into larger numbers.
   * **Case 3: `sum > target`**
     * The total sum is too high. Move `right` backward to tap into smaller numbers.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n^3)$
Sorting takes $\mathcal{O}(n \log n)$ time. The implementation relies on two outer tracking loops ($$\mathcal{O}(n^2)$$) combined with an inner two-pointer search that scans linearly ($$\mathcal{O}(n)$$). This establishes a combined worst-case time of $\mathcal{O}(n^3)$, which easily beats the brute-force approach.

### Space Complexity: $\mathcal{O}(1)$ or $\mathcal{O}(n)$
The algorithm itself operates dynamically in-place over the input vector. The precise memory consumption varies slightly based on the internal workspace demands of `std::sort` ($\mathcal{O}(\log n)$ stack spaces on average).

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force** | Run four nested loops to check every potential configuration of indices. | $\mathcal{O}(n^4)$ | $\mathcal{O}(1)$ |
| **Hash Map Acceleration** | Precompute the sums of all possible pairs and store their indices in a hash table. Loop through pairs again to check if `target - current_pair_sum` exists in the map, filtering out overlapping index allocations. | $\mathcal{O}(n^2)$ average | $\mathcal{O}(n^2)$ |