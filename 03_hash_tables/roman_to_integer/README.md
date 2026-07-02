# Roman to Integer

## Problem Statement
Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

| Symbol | Value |
| :---: | :---: |
| I | 1 |
| V | 5 |
| X | 10 |
| L | 50 |
| C | 100 |
| D | 500 |
| M | 1000 |

Given a roman numeral string `s`, convert it to an integer.

---

## Key Insight / Intuition
Roman numerals are usually written largest to smallest from left to right. However, there are instances where subtraction is used:
* If a smaller numeral precedes a larger numeral, it signifies **subtraction** (e.g., `IV` = $5 - 1 = 4$).
* If a smaller or equal numeral follows or stands alone, it signifies **addition** (e.g., `VI` = $5 + 1 = 6$).

Instead of processing special subtractive combinations (like `IV`, `IX`, `XL`) as separate multi-character tokens, we can scan the string character by character from left to right. At any index, we compare the current character's value to the next character's value. If the current value is smaller, it means this character is part of a subtractive pair, so we subtract its value from our total. Otherwise, we add it.

---

## Step-by-Step Approach
1. **Helper Mapping:** Utilize a fast helper routine `valueOf` (implemented via a `switch` statement) to translate Roman characters into their standard base-10 numerical equivalents.
2. **Scan Left-to-Right:** Iterate through the string using an index tracking pointer from `0` up to `size - 1`.
3. **Look-Ahead Comparison:** For each iteration:
   - Fetch `currentValue = valueOf(s[index])`.
   - Safely look ahead to fetch `nextValue = valueOf(s[index + 1])` (or `0` if we are at the very last character).
4. **Evaluate Condition:**
   - If `currentValue < nextValue`, subtract `currentValue` from the accumulator `result`.
   - If `currentValue >= nextValue`, add `currentValue` to the accumulator `result`.
5. **Return Total:** Once the loop completes, return `result`.

---

## Complexity Analysis

Let $N$ be the length of the input string `s`.

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm iterates through the string exactly once. Inside the loop, looking up character values via a `switch` block executes in constant $\mathcal{O}(1)$ time. Thus, the runtime scales linearly with the number of characters in the string.

* **Space Complexity:** $\mathcal{O}(1)$
  No auxiliary arrays, maps, or allocations are used. The conversion runs strictly in place utilizing primitive trackers (`result`, `currentValue`, `nextValue`), keeping memory consumption completely constant.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **String Replacement / Tokenization** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Replaces all subtractive pairs (e.g., `"IV"` $\rightarrow$ `"IIII"`) before adding values. Incurs higher memory footprint and string allocation overhead. |
| **Right-to-Left Traversal** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Iterates backward from the end, tracking the maximum value seen so far. Equally efficient but requires maintaining an extra running max state variable. |