# Permutation in String

## Problem Statement
Given two strings `s1` and `s2`, return `true` if `s2` contains a permutation of `s1`, or `false` otherwise.

In other words, return `true` if one of `s1` 's permutations is the substring of `s2`.

## Key Insight / Intuition
A permutation of a string is simply a rearrangement of its characters. This means any permutation of `s1` will have the exact same length as `s1` and the exact same character frequencies. 

Instead of generating all permutations, we can use a **Fixed-Size Sliding Window**. We maintain a window in `s2` of the same length as `s1`. As the window slides from left to right, we update a frequency array that tracks the balance of characters needed to form `s1`. By keeping a running counter `remaining` of how many character matches we still need, we can check if the current window is a valid permutation in $O(1)$ time.

## Approach

1. **Edge Case Check**: If `s1.size() > s2.size()`, `s2` cannot possibly contain a permutation of `s1`. Return `false` immediately.
2. **Initialize Frequency Balance**: Create a fixed-size array `balance` of size 26 (for lowercase English letters). Populate it with character frequencies from `s1`. Initialize a counter `remaining = s1.size()`.
3. **Sliding Window Traversal**: Slide a pointer `right` from `0` to `s2.size() - 1`:
   * **Acquire New Character**: Subtract 1 from the balance of the incoming character `s2[right]`. If its balance *before* subtraction was greater than 0, it means this character is needed for `s1`. Decrement `remaining`.
   * **Release Old Character**: If the window size exceeds `s1.size()` (i.e., `right >= windowSize`), the character leaving the window on the left is `s2[right - windowSize]`. Add 1 back to its balance. If its balance *after* addition becomes greater than 0, it means we are missing a character required by `s1`. Increment `remaining`.
   * **Check for Match**: If `remaining == 0`, the current window matches all character frequencies of `s1`. Return `true`.
4. **Return**: If the loop completes without `remaining` ever reaching 0, return `false`.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Where $n$ is the length of string `s2`. The algorithm visits each character in `s2` exactly once. All array indexing and counter modifications inside the loop take constant $O(1)$ time.
* **Space Complexity:** $O(1)$  
  The `balance` array uses a fixed size of 26 elements because the input is restricted to lowercase English letters. This requires strictly constant auxiliary space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Permutations)** | $O(m! \cdot m)$ | $O(m!)$ | Generates all permutations of `s1` and searches for them in `s2`. Extremely slow; practical only for tiny strings ($m \le 8$). |
| **Sliding Window with Full Array Compare** | $O(26 \cdot n) = O(n)$ | $O(1)$ | Slides a window of size $m$ and compares two frequency arrays of size 26 at each step. Correct, but less optimal due to array comparisons on every iteration. |

> **Note**: $m$ represents the length of `s1`, and $n$ represents the length of `s2`.