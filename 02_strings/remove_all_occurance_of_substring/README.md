# Remove All Occurrences of a Substring

## Problem Statement
Given two strings `s` and `part`, perform the following operation on `s` until all occurrences of the substring `part` are removed:
* Find the **leftmost** occurrence of the substring `part` and remove it from `s`.

Return `s` after removing all occurrences of `part`.

## Key Insight / Intuition
The naive approach uses string matching to find `part`, erases it, and shifts characters, which can lead to high time complexity due to repeated resizing and shifting. 

Instead, we can process the string character-by-character using a **Stack-like simulation** built directly inside our output string (`result`). We push characters from `s` into `result` one by one. Every time the length of `result` becomes at least as long as `part`, we inspect the trailing suffix of `result`. If it matches `part`, we immediately pop that substring off by truncating the string. This handles nested occurrences perfectly (e.g., if `part` is `"ab"`, processing `"a**ab**b"` will reduce to `"ab"`, which then reduces to `""`).

## Approach

1. **Initialize**: Create an empty string `result` to serve as our dynamic character stack.
2. **Character Scan**: Loop through each character `ch` in the input string `s`:
   * Append `ch` to the end of `result`.
   * **Suffix Match Verification**: Check if the current size of `result` is greater than or equal to the size of `part`.
   * If it is, compare the end of `result` with `part` using `result.compare()`.
   * **Truncate on Match**: If the suffix matches `part`, reduce the size of `result` by the length of `part` using `result.resize()`. This effectively pops the substring off the stack in $O(1)$ time.
3. **Return**: Once the entire string `s` is processed, `result` will contain the final cleaned string.

## Complexity Analysis

* **Time Complexity:** $O(n \cdot m)$  
  Where $n$ is the length of string `s` and $m$ is the length of string `part`. We iterate through `s` exactly $n$ times. At each character insertion, we perform a substring comparison that takes up to $O(m)$ time. 
* **Space Complexity:** $O(n)$  
  The auxiliary space is bounded by the size of the `result` string, which in the worst-case scenario (no occurrences of `part` found) will grow to the size of $n$.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Native Find and Erase (`std::string::find`)** | $O(n^2 / m)$ | $O(1)$ or $O(n)$ | repeatedly searches for `part` using built-in methods and uses `.erase()`. Slower due to heavy character shifting overhead on every deletion. |
| **KMP Algorithm with Stack** | $O(n + m)$ | $O(n + m)$ | Keeps a tracking array of matching indices alongside a character stack. Extremely fast and optimal for massive datasets, but overly verbose for a standard interview setting. |