# H-Index

## Problem Statement
Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their $i^{\text{th}}$ paper, return *the researcher's h-index*.

According to the definition of h-index on Wikipedia: The **h-index** is defined as the maximum value of $h$ such that the given researcher has published at least $h$ papers that have each been cited at least $h$ times.

---

## Key Insight / Intuition
The core task is to find a threshold value $h$ where $h$ papers have $\ge h$ citations.

Sorting the array in **descending order** simplifies this check:
* After sorting, if we are at zero-based index `i`, it means there are at least `i + 1` papers that each have $\ge \text{citations}[i]$ citations (since all previous papers in the sorted array have even higher or equal citation counts).
* The candidate value for $h$ at index `i` is `i + 1`.
* As long as `citations[i] >= i + 1`, the researcher satisfies having at least `i + 1` papers with at least `i + 1` citations.
* The moment `citations[i] < i + 1`, the condition breaks. The maximum valid $h$ is precisely equal to the index `i` itself.

---

## Step-by-Step Approach
1. **Sort Descending:** Sort the `citations` vector in non-ascending (descending) order using reverse iterators: `std::sort(citations.rbegin(), citations.rend())`.
2. **Scan and Compare:** Iterate through the array using index `index` from `0` to `size - 1`.
3. **Evaluate H-Threshold:**
   - At each `index`, check if `citations[index] < index + 1`.
   - If true, return `index` immediately, as this represents the count of papers processed so far that met the condition.
4. **All Papers Qualify:** If the loop finishes without returning, every paper has at least `size` citations. Return `size`.

---

## Complexity Analysis

Let $N$ be the number of papers (the size of the `citations` array).

* **Time Complexity:** $\mathcal{O}(N \log N)$
  The dominant operation is the initial sort step using `std::sort`, which operates in $\mathcal{O}(N \log N)$ time. The subsequent linear scan takes $\mathcal{O}(N)$ time.

* **Space Complexity:** $\mathcal{O}(1)$ or $\mathcal{O}(\log N)$
  The algorithm modifies the array in-place. Depending on the standard library implementation of `std::sort` (typically Introsort), the auxiliary stack space used for recursion during sorting is $\mathcal{O}(\log N)$. No additional dynamic memory allocations are made.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Counting Sort / Bucket Array** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Uses a frequency bucket array up to size $N$. Achieves linear time complexity at the cost of additional memory allocations. |
| **Binary Search on Answer** | $\mathcal{O}(N \log N)$ | $\mathcal{O}(1)$ | Binary searches the possible range $[0, N]$ and checks validity in linear time. Same overall asymptotic time complexity as sorting but with higher implementation overhead. |