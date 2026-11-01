# Is Subsequence

## Problem Statement
Given two strings `s` and `t`, return `true` if `s` is a **subsequence** of `t`, or `false` otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., `"ace"` is a subsequence of `"abcde"` while `"aec"` is not).

---

## Key Insight / Intuition
The problem asks whether all characters of string `s` appear in string `t` in the exact same relative order, though not necessarily consecutively.

We can solve this efficiently using a **Two-Pointer Greedy Approach**:
* Maintain one pointer (`sIndex`) for string `s` and another pointer (`tIndex`) for string `t`.
* Iterate through `t` from left to right. Whenever `t[tIndex]` matches `s[sIndex]`, we have successfully found the current character of `s`, so we advance `sIndex`.
* Regardless of whether a match occurs, we always advance `tIndex` to inspect the next character in `t`.
* If we successfully match all characters of `s` (i.e., `sIndex` reaches the end of `s`), then `s` is a valid subsequence.

---

## Step-by-Step Approach
1. **Cache Lengths:** Compute and store the lengths of both strings (`sLength` and `tLength`) as integers.
2. **Initialize Pointers:** Set `sIndex = 0` and `tIndex = 0`.
3. **Linear Scan:** Run a `while` loop as long as `sIndex < sLength` and `tIndex < tLength`:
   - If `s[sIndex] == t[tIndex]`, increment `sIndex` to look for the next character of `s`.
   - Always increment `tIndex` to continue scanning through `t`.
4. **Evaluate Result:** Return `true` if `sIndex == sLength` (meaning every character in `s` was matched in order), otherwise return `false`.

---

## Complexity Analysis

Let $S$ be the length of string `s` and $T$ be the length of string `t`.

* **Time Complexity:** $\mathcal{O}(T)$
  In the worst-case scenario, we iterate through the entire string `t` once. The runtime is strictly linear with respect to the length of `t`.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm uses only two integer index variables (`sIndex` and `tIndex`), requiring constant auxiliary space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Binary Search (Precomputation)** | $\mathcal{O}(T + S \log T)$ | $\mathcal{O}(T)$ | Ideal if there are *many* incoming `s` queries against a single static string `t`. Precomputes character indices in `t` using a hash map of vectors and binary searches for matching positions. |