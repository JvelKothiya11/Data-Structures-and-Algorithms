# Longest Happy Prefix (KMP LPS Array)

## Problem Statement
A string is called a **happy prefix** if is a non-empty prefix which is also a suffix (excluding itself).

Given a string `s`, return the **longest happy prefix** of `s`. Return an empty string `""` if no such prefix exists.

---

## Key Insight / Intuition
This problem is a direct application of the preprocessing step found in the **Knuth-Morris-Pratt (KMP)** pattern matching algorithm. Specifically, it computes the **LPS (Longest Prefix Suffix) array**.

The core idea is to find the longest proper substring that matches both the beginning and end of the string. Instead of checking every substring manually (which causes redundant computations), we maintain a `matchedLength` tracking the length of the current matching prefix. If a mismatch occurs at the current index, we use previous calculations stored in the array to "fallback" or shift back to the next longest viable prefix rather than restarting from zero.

---

## Step-by-Step Approach
1. **Edge Case:** If the string is empty, return `""` immediately.
2. **Initialize Tables:** Set up an array `longestPrefixSuffix` (commonly called the `lps` table) of size $N$ initialized to `0`. A tracker `matchedLength` is initialized to `0`.
3. **Iterate with Two Pointers:** Start looping from `index = 1` through the string:
   - **Character Match:** If `s[index] == s[matchedLength]`, it means the prefix match can be extended. We increment `matchedLength`, assign it to `longestPrefixSuffix[index]`, and move `index` forward.
   - **Mismatch with Positive Match Length:** If the characters do not match but `matchedLength > 0`, we fallback to the previous longest match: 

     `matchedLength = longestPrefixSuffix[matchedLength - 1]`

    > **Note**: We do not increment `index` here; we re-evaluate the new boundary.
   - **Mismatch with Zero Match Length:** If there is no prefix match possible at all, we set `longestPrefixSuffix[index] = 0` (implicitly done) and simply increment `index`.
4. **Extract Result:** The final element of the LPS table (`longestPrefixSuffix.back()`) yields the length of the longest proper prefix that is also a suffix. Use `.substr(0, length)` to extract and return it.

---

## Complexity Analysis

Let $N$ be the length of the string `s`.

* **Time Complexity:** $\mathcal{O}(N)$
  Even though the loop contains an inner fallback condition that does not increment `index`, `matchedLength` can at most increase by $1$ per step. The fallback statement strictly reduces `matchedLength`. Since `matchedLength` cannot decrease more times than it increases, the total number of operations is bounded linearly by $2N$. Thus, the time complexity is $\mathcal{O}(N)$.

* **Space Complexity:** $\mathcal{O}(N)$
  The algorithm requires an auxiliary integer array/vector of size $N$ to hold the `longestPrefixSuffix` values for fallback calculations.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Slice & Compare)** | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | Extracts every prefix/suffix combo and checks equality. Easily triggers Time Limit Exceeded (TLE) for large strings. |
| **Rabin-Karp Rolling Hash** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Computes rolling hashes from left-to-right and right-to-left. Fast and saves space, but risks hash collisions unless using a double-hash mechanism. |