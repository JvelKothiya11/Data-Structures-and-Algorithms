# Substring with Concatenation of All Words

## Problem Statement
You are given a string `s` and an array of strings `words`. All the strings of `words` are of **the same length**.

A **concatenated substring** in `s` is a substring that contains all the strings of any permutation of `words` concatenated together.
* For example, if `words = ["ab","cd","ef"]`, then `"abcdef"`, `"abefcd"`, `"cdabef"`, `"cdefab"`, `"efabcd"`, and `"efcdab"` are all concatenated substrings. `"acdbef"` is not because it is not a concatenation of any permutation of `words`.

Return *the starting indices of all the concatenated substrings in `s`*. You can return the answer in **any order**.

---

## Key Insight / Intuition
Because all strings in `words` share an identical fixed length (`wordLength`), any valid concatenated substring must span a total length of `wordCount * wordLength`. 

A naive check for every possible starting position can result in redundant substring extractions. Instead, we can use a **Sliding Window with Offset Iteration**:
1. **Partition by Offsets:** Since every word has length `wordLength`, we only need to slide our window starting from `wordLength` distinct offsets (from `0` to `wordLength - 1`). This ensures we inspect every possible alignment without overlapping or missing windows.
2. **Word-Level Sliding Window:** Within each offset stream, we treat words as individual atomic tokens rather than single characters. We maintain a frequency map of the words currently inside our sliding window (`windowFrequency`) and compare it against the target frequency map (`requiredFrequency`).
3. **Greedy Adjustments:** 
   - If we encounter a word not present in `words`, we completely reset our window.
   - If a word appears more times than allowed, we shrink the window from the left until the frequency constraint is satisfied.
   - When the number of valid matched words equals `wordCount`, we record the starting `left` index.

---

## Step-by-Step Approach
1. **Edge Case & Bounds Check:** Return an empty result if `s` or `words` is empty, or if the total length of all words combined exceeds the length of string `s`.
2. **Build Frequency Map:** Count the occurrence of each word in `words` and store it in `requiredFrequency`.
3. **Offset Iteration Loop:** Loop an offset variable from `0` up to `wordLength - 1`:
   - Initialize `left = offset`, `right = offset`, `matchedWords = 0`, and a clear `windowFrequency` map for this offset stream.
4. **Slide Window by Word Blocks:** While `right + wordLength <= stringLength`:
   - Extract the `currentWord` of length `wordLength` starting at `right`, and advance `right` by `wordLength`.
   - **Invalid Word Check:** If `currentWord` is not in `requiredFrequency`, reset `windowFrequency`, reset `matchedWords = 0`, set `left = right`, and `continue`.
   - **Add Word to Window:** Increment its count in `windowFrequency` and increment `matchedWords`.
   - **Shrink Excess:** While `windowFrequency[currentWord] > requiredFrequency.at(currentWord)`:
     - Remove the leftmost word (`leftWord`) from `windowFrequency`, decrement `matchedWords`, and advance `left` by `wordLength`.
   - **Match Found:** If `matchedWords == wordCount`, record the current `left` index into `result`, slide past the leftmost word to keep searching for overlapping or subsequent matches.
5. **Return Result:** Return the final `result` vector containing all starting indices.

---

## Complexity Analysis

Let $S$ be the length of string `s`, $N$ be the number of words in `words`, and $L$ be the length of each word.

* **Time Complexity:** $\mathcal{O}(L \times S)$
  There are $L$ offset streams. For each offset, the `right` pointer traverses the string `s` in increments of $L$ words, meaning each character/word block is processed in linear time relative to the string length. String slicing and map lookups take proportional time bounded by word length $L$.

* **Space Complexity:** $\mathcal{O}(N \times L)$
  Requires auxiliary hash maps (`requiredFrequency` and `windowFrequency`) to store up to $N$ unique words of length $L$.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Substring Matching)** | $\mathcal{O}(S \times N \times L)$ | $\mathcal{O}(N \times L)$ | Checks every starting index by matching all $N$ words sequentially. Prone to redundant checks and TLE on large inputs. |