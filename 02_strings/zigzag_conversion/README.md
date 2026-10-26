# Zigzag Conversion

## Problem Statement
The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```text
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: `"PAHNAPLSIIGYIR"`

Write the code that will take a string and make this conversion given a number of rows:
`string convert(string s, int numRows);`

---

## Key Insight / Intuition
The problem can be modeled as tracking a vertical cursor that bounces up and down across the specified number of rows:
1. **Simulation via Direction Flag:** As we iterate through each character of the string, we place it into its corresponding row. 
2. **Boundary Reflection:** When the cursor reaches the top row (`row 0`), the direction changes to downward (`+1`). When it reaches the bottom row (`numRows - 1`), the direction flips to upward (`-1`).
3. **Aggregation:** Once every character is sorted into its respective row bucket, concatenating the rows from top to bottom yields the exact zigzag string sequence.

---

## Step-by-Step Approach
1. **Edge Case Handling:** If `numRows <= 1` or `numRows >= s.size()`, no zigzag pattern can be formed; return the original string `s` immediately.
2. **Row Buffers Initialization:** Create a vector of `std::string` of size `numRows` to store the characters for each row.
3. **Traversal and Placement:** 
   - Maintain `currentRow = 0` and `direction = 1`.
   - Loop through each character `ch` in `s`:
     - Append `ch` to `rows[currentRow]`.
     - If `currentRow == 0`, set `direction = 1`.
     - Else if `currentRow == numRows - 1`, set `direction = -1`.
     - Update `currentRow += direction`.
4. **String Concatenation:** Pre-allocate a result string using `result.reserve(s.size())`, then append each row string sequentially to assemble the final output.

---

## Complexity Analysis

Let $N$ be the length of the input string `s` and $R$ be the number of rows (`numRows`).

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm iterates through each character of the string exactly once to distribute them into row buckets, followed by a linear concatenation pass of total length $N$. Thus, time complexity scales linearly with the string size.

* **Space Complexity:** $\mathcal{O}(N)$
  The auxiliary storage required by the `rows` vector and the `result` string holds all $N$ characters of the input string across buffers.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Direct Mathematical Indexing** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Computes character positions directly based on cycle lengths ($2 \times \text{numRows} - 2$). Achieves $\mathcal{O}(1)$ auxiliary space at the expense of more complex index arithmetic.