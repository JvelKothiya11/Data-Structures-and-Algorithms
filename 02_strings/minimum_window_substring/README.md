# Minimum Window Substring

## Problem Statement
Given two strings `s` and `t` of lengths `m` and `n` respectively, return the **minimum window substring** of `s` such that every character in `t` (including duplicates) is included in the window. If there is no such substring, return the empty string `""`.

The test cases are generated such that the answer is **unique**.

---

## Key Insight / Intuition
The problem asks for an optimal contiguous subarray (substring), which heavily hints at using a **Sliding Window** approach with two pointers (`windowStart` and `windowEnd`).

Instead of re-checking the window from scratch every time, we maintain a frequency map of the required characters. We expand our window by moving `windowEnd` to the right until it contains all characters from `t`. Once a valid window is found, we try to contract it from the left by moving `windowStart` forward to find the smallest possible valid substring. 

By tracking the number of `remaining` characters needed to satisfy the requirements of `t`, we avoid scanning the entire map on every pointer shift.

---

## Step-by-Step Approach
1. **Edge Case Check:** If `t` is larger than `s`, it is impossible to find a valid window; return `""` immediately.
2. **Frequency Initialization:** Build a frequency map (using a fixed-size array of 128 for ASCII mapping) to count occurrences of characters in `t`.
3. **Expand the Window:** Move the `windowEnd` pointer from left to right:
   - Decrement the count of the current character `rightChar` in the frequency map.
   - If the character was positively required (i.e., its count in the map was $> 0$ before decrementing), decrement the `remaining` counter.
4. **Contract the Window:** While `remaining == 0` (all characters from `t` are present in the current window):
   - Calculate the window size (`windowEnd - windowStart + 1`). If it is smaller than our global minimum, update `minimumLength` and save `bestStart`.
   - Slide `windowStart` to the right to see if the window remains valid with a shorter length.
   - Restore the character at `windowStart` into the frequency map. If its count becomes positive ($> 0$), it means a vital character from `t` was removed, so we increment `remaining` to break the contraction loop.
5. **Return Result:** If `minimumLength` was updated, extract and return the substring using `s.substr(bestStart, minimumLength)`. Otherwise, return `""`.

---

## Complexity Analysis

Let $M$ be the length of string `s` and $N$ be the length of string `t`.

* **Time Complexity:** $\mathcal{O}(M + N)$
  - Building the frequency map for `t` takes $\mathcal{O}(N)$ time.
  - The `windowEnd` pointer visits each character in `s` exactly once. The `windowStart` pointer also moves progressively forward and visits each character at most once. Hence, the two-pointer traversal takes at most $\mathcal{O}(2M) = \mathcal{O}(M)$ steps.
  - Total Time Complexity is linear: $\mathcal{O}(M + N)$.

* **Space Complexity:** $\mathcal{O}(1)$
  - The frequency array has a fixed size of `128` (representing standard ASCII characters). Because the space allocation does not scale with the sizes of input strings `s` or `t`, the auxiliary space complexity remains constant.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Check Substrings)** | $\mathcal{O}(M^2 \cdot N)$ | $\mathcal{O}(1)$ | Generates all possible substrings and counts characters. Extremely slow; will result in Time Limit Exceeded (TLE). |
| **Filtered Sliding Window** | $\mathcal{O}(M + N)$ | $\mathcal{O}(M)$ | Creates a separate list filtering only the characters that exist in `t` along with their indices. Useful when $M \gg N$, but uses more space. |