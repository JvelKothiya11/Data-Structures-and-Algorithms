# Integer to Roman

## Problem Statement
Seven different symbols represent Roman numerals with the following values:

| Symbol | Value |
| :--- | :--- |
| I | 1 |
| V | 5 |
| X | 10 |
| L | 50 |
| C | 100 |
| D | 500 |
| M | 1000 |

Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral involves the following rules:
* If the value does not start with 4 or 9, choose the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder.
* If the value starts with 4 or 9, use the **subtractive form** (e.g., $4$ is `IV`, $9$ is `IX`, $40$ is `XL`, $400$ is `CD`, etc.).

Given an integer, convert it to a Roman numeral.

---

## Key Insight / Intuition
Instead of handling complex conditional branches for every decimal place (thousands, hundreds, tens, units) and their respective subtractive prefixes, we can model the problem as a **Greedy Subtraction** over a predefined lookup table.

By storing all standard Roman symbol combinations—including the essential subtractive pairs like `CM` (900), `CD` (400), `XC` (90), `XL` (40), `IX` (9), and `IV` (4)—in strict **descending order of their numerical values**, the problem simplifies:
* We repeatedly subtract the largest possible value from our number.
* Each time we subtract a value, we append its corresponding Roman symbol to our result string. 
* Because Roman numerals naturally require the largest symbols first, this greedy approach is guaranteed to produce the correct canonical representation.

---

## Step-by-Step Approach
1. **Define Lookup Tables:** Create two parallel `constexpr` arrays:
   - `values`: Contains all 13 valid integer values in descending order (`1000`, `900`, `500`, `400`, `100`, `90`, `50`, `40`, `10`, `9`, `5`, `4`, `1`).
   - `symbols`: Contains the corresponding Roman string literals (`"M"`, `"CM"`, `"D"`, `"CD"`, `"C"`, `"XC"`, `"L"`, `"XL"`, `"X"`, `"IX"`, `"V"`, `"IV"`, `"I"`).
2. **Initialize Result String:** Declare an empty `std::string` and pre-allocate memory using `result.reserve(16)` to prevent dynamic reallocations (since the maximum standard Roman numeral for 3999 is 15 characters long).
3. **Greedy Subtraction Loop:** Iterate through each index `i` of the arrays:
   - While `num` is greater than or equal to `values[i]`:
     - Subtract `values[i]` from `num`.
     - Append `symbols[i]` to `result`.
4. **Return Result:** Return the fully constructed `result` string.

---

## Complexity Analysis

Let $N$ be the input integer value.

* **Time Complexity:** $\mathcal{O}(1)$
  Since the input value is bounded within a fixed range ($1 \le \text{num} \le 3999$), the maximum number of subtractions is strictly upper-bounded (at most 15 operations for 3888, `MMMDCCCLXXXVIII`). Thus, the execution time is constant with respect to the input size.

* **Space Complexity:** $\mathcal{O}(1)$
  The algorithm uses constant auxiliary memory. The storage for arrays is `constexpr` (compiled into the binary), and the result string requires at most 16 bytes of heap/stack space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Digit-by-Digit Mapping (Arrays of Strings)** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Separates thousands, hundreds, tens, and units into lookup arrays. Very fast, but requires more verbose conditional indexing. |