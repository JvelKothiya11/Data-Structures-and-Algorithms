# Text Justification

## Problem Statement
Given an array of strings `words` and an integer `maxWidth`, format the text such that each line has exactly `maxWidth` characters and is **fully (left and right) justified**.

You should pack your words in a **greedy** approach; that is, pack as many words as you can in each line. Pad extra spaces `' '` when necessary so that each line has exactly `maxWidth` characters.

Rules:
* Extra spaces between words should be distributed **as evenly as possible**.
* If the number of spaces on a line does not divide evenly between words, the **empty slots on the left** are assigned more spaces than the slots on the right.
* The **last line** of text, and any line containing **only one word**, should be **left-justified**: no extra space is inserted between words, and the remaining spaces are padded at the end.

Each word has length in the range $[1, maxWidth]$, and every word contains only non-space characters.

## Key Insight / Intuition
This problem is a pure **simulation** problem that splits cleanly into two independent sub-tasks:

1. **Line Packing**: decide *which* words belong on each line.
2. **Space Distribution**: decide *how many* spaces go into each gap on that line.

For a line holding $w$ words, there are exactly $w - 1$ gaps, and each gap needs **at least one space**. So a candidate set of words fits on a line only if:

$$\text{totalWordChars} + (w - 1) \le maxWidth$$

Once the words of a line are fixed, the leftover spaces are shared among the gaps using simple integer division and remainder, which automatically gives the leftmost gaps the extra spaces.

## Approach

The algorithm processes the words in a single left-to-right pass:

1. **Phase 1 (Greedy Line Packing)**:
   * Start at `lineStart = index` and keep a running sum `totalWordChars` of the word lengths on the current line.
   * Try to add `words[index]`. The width it would require is `totalWordChars + wordLength + wordsOnLine`, where `wordsOnLine` is the number of spaces (one per existing gap) that must separate the words.
   * If `requiredWidth > maxWidth`, stop; otherwise accept the word and advance `index`.
2. **Phase 2 (Build the Justified Line)**:
   * Let `gaps = wordsOnLine - 1`.
   * **Left-justify case** (`isLastLine` or `gaps == 0`): join the words with a single space and pad the remainder of the line with trailing spaces.
   * **Full-justify case**: compute
     * `totalSpaces = maxWidth - totalWordChars`
     * `baseSpaces = totalSpaces / gaps`
     * `extraSpaces = totalSpaces % gaps`
   * Place `baseSpaces` spaces after every word except the last, plus **one extra space** for the first `extraSpaces` gaps (the leftmost ones). The last word on the line gets no trailing spaces.
3. Push the finished line into `result` and repeat from the new `index` until all words are consumed.

## Mathematical Derivation
Let:
* $w$ = Number of words placed on the current line.
* $L$ = Total number of characters in those $w$ words (`totalWordChars`).
* $g = w - 1$ = Number of gaps between words.
* $S = maxWidth - L$ = Total spaces that must be distributed.

Each gap receives a base amount, and the remainder is handed out one by one from the left:

$$S = g \cdot q + r, \quad q = \left\lfloor \frac{S}{g} \right\rfloor, \quad r = S \bmod g$$

So the first $r$ gaps receive $q + 1$ spaces and the remaining $g - r$ gaps receive $q$ spaces. Verifying that the line width is exactly $maxWidth$:

$$L + r(q + 1) + (g - r)q = L + gq + r = L + S = maxWidth$$

The greedy fitting condition guarantees every gap gets at least one space, since a line is accepted only when:

$$L + g \le maxWidth \implies S \ge g \implies q \ge 1$$

## Complexity Analysis

* **Time Complexity:** $O(N)$  
  Here $N$ is the total number of characters across all words. Every word is examined once while packing and appended once while building a line, and padding adds at most $maxWidth$ characters per line, which is proportional to the output size.
* **Space Complexity:** $O(1)$ (excluding output)  
  Only scalar variables (`index`, `lineStart`, `totalWordChars`, `gaps`, etc.) and one temporary line string of size `maxWidth` are used. The returned `result` vector of size $O(N)$ is required output and not counted as extra space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Greedy Packing? | Pros / Cons |
| :--- | :--- | :--- | :--- | :--- |
| **Group Lines First, Justify Later** | $O(N)$ | $O(W)$ | Yes | Stores each line's words in a temporary list before formatting. Easier to read but uses extra memory. |
| **Character-by-Character Space Insertion (Round Robin)** | $O(N \cdot maxWidth)$ | $O(maxWidth)$ | Yes | Adds spaces one at a time cycling through gaps. Simple but slower than division and modulo. |
| **Dynamic Programming (Minimum Raggedness / Knuth–Plass)** | $O(W^2)$ | $O(W)$ | **No** | Produces visually optimal paragraphs, but violates the problem's **greedy packing** requirement. |