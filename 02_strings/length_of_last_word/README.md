# Length of Last Word

## Problem Statement
Given a string `s` consisting of words and spaces, return *the length of the **last** word in the string*.

A **word** is a maximal substring consisting of non-space characters only. The input string may contain trailing spaces, which should be ignored when identifying the final word.

---

## Key Insight / Intuition
The naive approach might involve splitting the string from left to right using spaces as a delimiter. However, since we only care about the **last** word, scanning from left to right does unnecessary work.

The optimal strategy is a **Backward Scan (Right-to-Left)**. By starting at the end of the string, we can:
1. Skip any trailing whitespace characters first.
2. Count the characters of the very first word we encounter.
3. Stop immediately when we hit a space after that word (or reach the start of the string).

---

## Step-by-Step Approach
1. **Initialize Pointer:** Set an `index` pointer to the last element of the string (`s.size() - 1`).
2. **Skip Trailing Spaces:** Move the `index` pointer backward as long as the current character is a space (`' '`) and `index >= 0`. This clears the trailing padding.
3. **Count Word Length:** Initialize a `length` counter to `0`. 
4. **Read Last Word:** Continue moving the `index` pointer backward. For every non-space character encountered, increment `length`.
5. **Termination:** The loop naturally stops either when a space character is hit (marking the boundary of the last word) or when `index` runs out of bounds (meaning the entire string was just one word). Return `length`.

---

## Complexity Analysis

Let $N$ be the length of the string `s`.

* **Time Complexity:** $\mathcal{O}(N)$
  In the worst-case scenario (e.g., a string with only spaces or a single long word), the algorithm scans the entire string once. In the best/average case, it only scans the length of the last word and its trailing spaces, making it highly efficient. The upper bound remains tightly bounded at $\mathcal{O}(N)$.

* **Space Complexity:** $\mathcal{O}(1)$
  The operations are performed in place using only a few local integer variables (`index`, `length`) to maintain position and size state. No extra copies of the string or substrings are allocated.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **String Tokenization (`std::stringstream`)** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Parses all words into dynamic memory allocations and reads the final entry. Clean syntax but heavy overhead due to extra allocations. |
| **Forward Pass with Trackers** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Loops from index 0 to $N-1$, resetting a temporary counter whenever a new word starts. Traverses the entire string blindly, even if the last word is tiny. |