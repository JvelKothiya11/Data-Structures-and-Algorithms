# String Compression

## Problem Statement
Given an array of characters `chars`, compress it using the following algorithm:
1. Begin with an empty string.
2. For each group of consecutive repeating characters in `chars`:
   - If the group's length is `1`, append the character to the string.
   - Otherwise, append the character followed by the group's length.

The compressed string must be stored **in-place** within the input array `chars`. The function should return the new length of the array after compression.

---

## Key Insight / Intuition
To modify the array in-place without using extra space, we can utilize a **Two-Pointer Approach** (`read` and `write`). 
* The `read` pointer scans through the array to identify contiguous blocks of identical characters.
* The `write` pointer tracks where the next compressed character or digit frequency should be inserted.

Because the compressed length of a group is always less than or equal to its original length (e.g., `"aaaa"` $\rightarrow$ `"a4"`), the `write` pointer will never overtake the `read` pointer, making in-place modification completely safe.

---

## Step-by-Step Approach
1. **Initialize Pointers:** Set both `read` and `write` pointers to index `0`.
2. **Identify Consecutive Groups:** Loop through the array with the `read` pointer. Mark the start of the current group (`groupStart = read`).
3. **Count Frequency:** Move the `read` pointer forward as long as the consecutive characters match the character at `groupStart`. The length of the current group is calculated as:
   $$\text{count} = \text{read} - \text{groupStart}$$
4. **Write the Character:** Record the character at `chars[write]` and increment `write`.
5. **Write the Frequency (If > 1):** If the character occurs more than once, convert the count to a string/characters and write each digit sequentially using the `write` pointer.
6. **Return Result:** Repeat until the entire array is processed. The final value of `write` represents the length of the newly compressed array.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(N)$
  Each character in the array is visited at most twice (once by the inner loop determining the group size, and once by the outer loop iteration). Converting the count to a string takes $\mathcal{O}(\log_{10}(\text{count}))$ time, which is negligible. Thus, the total time complexity scales linearly with the size of the array $N$.

* **Space Complexity:** $\mathcal{O}(1)$
  The compression is performed in-place using only a few primitive integer variables (`read`, `write`, `groupStart`). The temporary string used to convert the frequency requires minimal space (at most a few bytes for very large counts), satisfying the constant extra space constraint.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Out-of-Place (Extra Array)** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Easier to implement but violates the in-place memory constraint. |
| **String Reconstruction** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Concatenating into a `std::string` first requires extra space and copies data back to the array. |