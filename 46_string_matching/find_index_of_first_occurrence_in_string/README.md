# Find the Index of the First Occurrence in a String (strStr)

## Problem Statement
Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

---

## Key Insight / Intuition
The solution utilizes a **Sliding Window Sliding/Brute-Force Substring Search** (often called the naive string-matching algorithm). 

We slide the `needle` over the `haystack` one character at a time. For each position, we check if the characters match. A crucial optimization is the search boundary: we don't need to check starting positions in the `haystack` where the remaining characters are fewer than the length of the `needle`. This sets our upper iteration limit exactly to `haystackLength - needleLength`.

---

## Step-by-Step Approach
1. **Edge Case Handling:** - If `needle` is empty, return `0` immediately.
   - If `needle` is longer than `haystack`, it cannot exist within it; return `-1`.
2. **Outer Loop (Window Slidings):** Iterate through `haystack` using a `startIndex` pointer. The loop safely stops at `haystackLength - needleLength`.
3. **Inner Loop (Character Matching):** For each `startIndex`, initialize an `offset` pointer starting at `0`. Compare `haystack[startIndex + offset]` with `needle[offset]`.
4. **Early Mismatch Break:** Keep incrementing `offset` as long as the characters match. The moment a mismatch occurs, the inner loop terminates, and the window slides forward by incrementing `startIndex`.
5. **Match Confirmation:** If the inner loop finishes and `offset` equals `needleLength`, it means the entire `needle` was successfully matched. Return the current `startIndex`.
6. **Fallback Return:** If the outer loop finishes without finding a match, return `-1`.

---

## Complexity Analysis

Let $H$ be the length of the `haystack` string and $N$ be the length of the `needle` string.

* **Time Complexity:** $\mathcal{O}((H - N + 1) \cdot N)$
  In the worst-case scenario (e.g., `haystack` = `"aaaaa"`, `needle` = `"aab"`), the outer loop runs $H - N + 1$ times, and for each position, we compare up to $N$ characters. This results in an overall upper bound of $\mathcal{O}(H \cdot N)$. However, for typical text inputs, the inner loop breaks very early, yielding near-linear average performance.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm searches entirely in-place by comparing characters directly at their respective memory indices. No additional strings, substrings, or temporary buffers are generated, requiring constant memory overhead.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **KMP (Knuth-Morris-Pratt)** | $\mathcal{O}(H + N)$ | $\mathcal{O}(N)$ | Precomputes a lookup table (LPS array) to bypass redundant character re-checks. Highly efficient but more complex to code. |
| **Rabin-Karp (Rolling Hash)** | $\mathcal{O}(H + N)$ average | $\mathcal{O}(1)$ | Compares hash values of the sliding window with `needle`. Fast but handles hash collision edge cases. |