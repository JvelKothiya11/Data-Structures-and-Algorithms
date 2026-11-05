# Find the Distance Value Between Two Arrays

## Problem Statement
Given two integer arrays `arr1` and `arr2` and an integer `d`, return *the distance value between the two arrays*.

The distance value is defined as the number of elements `arr1[i]` such that there is **not** any element `arr2[j]` where `|arr1[i] - arr2[j]| <= d`.

---

## Key Insight / Intuition
A brute-force approach compares every element in `arr1` against every element in `arr2`, resulting in an $\mathcal{O}(M \times N)$ time complexity. We can significantly optimize this by leveraging **Binary Search**:
1. **Sort the Second Array:** If we sort `arr2`, we can efficiently query the closest elements for any value from `arr1` using binary search (`std::lower_bound`).
2. **Bounding Candidates:** For any given element in `arr1`, its closest potential matches in `arr2` are strictly limited to:
   - The smallest element in `arr2` that is greater than or equal to `arr1[i]` (found via `std::lower_bound`).
   - The largest element in `arr2` that is strictly less than `arr1[i]` (the element immediately preceding the iterator).
3. We only need to check these two closest neighbors. If neither neighbor violates the distance condition ($\le d$), then no other element in `arr2` can violate it either, making `arr1[i]` a valid contributor to the distance value.

---

## Step-by-Step Approach
1. **Sort `arr2`:** Sort the elements of `arr2` in non-decreasing order using `std::sort` to enable binary search.
2. **Initialize Counter:** Set `distanceValue = 0` to track the count of valid elements from `arr1`.
3. **Iterate Through `arr1`:** For each `value` in `arr1`:
   - Use `std::lower_bound` to find the first element in `arr2` that is $\ge$ `value`.
   - **Check Right Candidate:** Verify if a valid right neighbor exists (`it != arr2.end()`) and if its absolute difference from `value` is less than or equal to `d`.
   - **Check Left Candidate:** Verify if a valid left neighbor exists (`it != arr2.begin()`) and if its absolute difference from `value` is less than or equal to `d`.
   - **Evaluate Condition:** If neither the right nor the left candidate violates the distance condition, increment `distanceValue`.
4. **Return Result:** Return the final accumulated `distanceValue`.

---

## Complexity Analysis

Let $M$ be the size of `arr1` and $N$ be the size of `arr2`.

* **Time Complexity:** $\mathcal{O}(N \log N + M \log N)$
  - Sorting `arr2` takes $\mathcal{O}(N \log N)$ time.
  - Performing a binary search (`std::lower_bound`) for each of the $M$ elements in `arr1` takes $\mathcal{O}(M \log N)$ time.

* **Space Complexity:** $\mathcal{O}(\log N)$ or $\mathcal{O}(1)$
  - Auxiliary space depends on the sorting implementation stack depth ($\mathcal{O}(\log N)$ for introsort). The search itself requires constant auxiliary space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $\mathcal{O}(M \times N)$ | $\mathcal{O}(1)$ | Compares every pair of elements. Extremely slow and inefficient for large arrays. |