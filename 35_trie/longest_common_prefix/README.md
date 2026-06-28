# Longest Common Prefix

## Problem Statement
Given an array of strings `strs`, find the longest common prefix string amongst them. If there is no common prefix, return an empty string `""`.

A prefix is a collection of characters at the beginning of a string. For a prefix to be "common", it must look identical at the start of every single string in the input array.

---

## Key Insight / Intuition
The solution uses **Vertical Scanning**. 

Instead of comparing the first string entirely with the second, then the third, and so on (horizontal scanning), we look at the strings like a 2D grid of characters. We compare characters column by column:
* First, we compare the $0^{\text{th}}$ character of all strings.
* Then, we compare the $1^{\text{st}}$ character of all strings, and so forth.

The moment we encounter a mismatch between characters or reach the end of any string, we can confidently stop. Everything matched up to that column is our longest common prefix.

---

## Step-by-Step Approach
1. **Handle Edge Cases:** (Implicitly handled) If the input array is empty, the loop bounds naturally return an empty prefix. 
2. **Outer Loop (Column-by-Column):** Iterate through each character index (`column`) of the very first string `strs[0]`. This character serves as our `expected` benchmark for the current column.
3. **Inner Loop (Row-by-Row):** Iterate through the remaining strings (`row` from `1` to `wordCount - 1`) and check two conditions:
   - **Out of Bounds Check:** If the current `column` index is greater than or equal to the length of `strs[row]`, it means we have completely exhausted one of the strings.
   - **Character Mismatch Check:** If `strs[row][column]` does not match our `expected` character.
4. **Early Return:** If either condition in Step 3 is met, return the substring of `strs[0]` from index `0` up to (but excluding) the current `column`.
5. **Full Match Return:** If the loops finish without any mismatch, it means the entire first string `strs[0]` is the common prefix. Return `strs[0]`.

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(S)$
  Where $S$ is the sum of all characters in all strings. In the worst-case scenario (where all strings are identical), the algorithm will look at every character. If there are $N$ strings of average length $M$, the worst-case time complexity is $\mathcal{O}(N \times M)$. However, the vertical scanning approach provides excellent best-case behavior $\mathcal{O}(N \times K)$, where $K$ is the length of the common prefix.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm performs the scan entirely in place without utilizing any additional data structures that scale with input size. The space required for the returned substring is a requirement of the output, not extra overhead.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Horizontal Scanning** | $\mathcal{O}(S)$ | $\mathcal{O}(1)$ | Compares `prefix = match(strs[0], strs[1])` sequentially. Can do unnecessary work if the last string has a mismatch at index 0. |
| **Sorting-Based** | $\mathcal{O}(N \cdot M \log N)$ | $\mathcal{O}(1)$ or $\mathcal{O}(M)$ | Sorts the array and only compares the first and last string. Good if array is already sorted, but otherwise slower due to sorting overhead. |
| **Divide and Conquer** | $\mathcal{O}(S)$ | $\mathcal{O}(M \log N)$ | Splits array in halves to find prefixes recursively. Adds overhead due to recursive call stack space. |