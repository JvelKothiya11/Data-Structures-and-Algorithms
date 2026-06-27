# Reverse Words in a String

## Problem Statement
Given an input string `s`, reverse the order of the **words**. A word is defined as a sequence of non-space characters. The words in `s` will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space. Note that `s` may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words, with no leading or trailing spaces.

## Key Insight / Intuition
The dual-reversal technique is an elegant way to solve this problem. 

If we reverse the entire string first, the words will be placed in their correct relative final positions (the last word moves to the front, the first word moves to the back). However, reversing the entire string also reverses the characters *within* each individual word. To fix this, we can iterate through the reversed string, extract each individual word while cleanly ignoring extra spaces, and append its characters in backward order to restore the correct spelling.

## Approach

1. **Global Reversal**: Reverse the entire string `s` using `std::reverse`.
2. **Word Extraction & Local Reversal**: Use an index pointer to scan through the globally reversed string:
   * **Skip Spaces**: Increment `index` to skip over any leading spaces or multiple spaces between words.
   * **Mark Word Boundaries**: Save the starting position of a word (`start = index`), then advance `index` until a space or the end of the string is reached.
   * **Append and Delimit**: If our `result` string already contains words, append a single spaces delimiter (`' '`) before adding the next word.
   * **Invert Word Characters**: Read the identified word backwards from `index - 1` down to `start` and append it to `result`. This un-reverses the character order of the word.
3. **Return**: Return the newly constructed `result` string, which is guaranteed to have clean spacing.

## Algorithmic Visualization

Consider the input string `s = "  hello world  "`:
* **Step 1 (Global Reverse)**: `"  dlrow olleh  "`
* **Step 2 (Skip spaces & find first word)**: Pointer finds word `"dlrow"` from index 2 to 6.
* **Step 3 (Append inverted word)**: `result = "world"`
* **Step 4 (Skip spaces & find next word)**: Pointer finds word `"olleh"` from index 8 to 12.
* **Step 5 (Append delimiter & inverted word)**: `result = "world hello"`

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  The global reversal takes $O(n)$ time. The subsequent `while` loop visits each character in the string at most twice (once during the boundary scan and once when copying characters to the `result` string), ensuring a strictly linear time complexity.
* **Space Complexity:** $O(n)$  
  A new `result` string is built to handle the structural cleanup of multiple spaces. 

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Stringstream Tokenization** | $O(n)$ | $O(n)$ | Uses `std::stringstream` to naturally parse words by spacing, pushes them to a vector, and joins them backwards. Highly readable but has minor C++ stream formatting overhead. |
| **In-Place Two-Pointer Shift** | $O(n)$ | $O(1)$ | Performs global and local reversals directly within `s`, then uses a two-pointer shift algorithm to erase extra spaces in-place. Fully optimal but structurally harder to write cleanly. |