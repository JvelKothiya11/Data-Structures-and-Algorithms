# Group Anagrams

## Problem Statement
Given an array of strings `strs`, group the **anagrams** together. You can return the answer in any order.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once. For example, `"eat"`, `"tea"`, and `"ate"` are all anagrams of each other.

---

## Key Insight / Intuition
The core property of anagrams is that they contain the exact same characters with the exact same frequencies. Therefore, if we normalize or sort the characters of any anagram, they will yield the identical string. 

We can treat this sorted version as a universal **"signature"** or **"key"**. By mapping each unique signature to a list of its original words using a hash map (`std::unordered_map`), we can efficiently cluster all anagrams together in a single pass.

---

## Step-by-Step Approach
1. **Initialize Hash Map:** Create an `std::unordered_map` where the key is a `std::string` (the sorted signature) and the value is a `std::vector<std::string>` (the group of matching anagrams). Pre-allocate memory using `.reserve()` to optimize insertion.
2. **Generate Signatures:** Iterate through each `word` in the input array:
   - Make a copy of the word called `signature`.
   - Sort the characters of `signature` alphabetically using `std::sort`.
3. **Group by Key:** Push the original `word` into the hash map under its sorted `signature` key.
4. **Collect Results:** Create a 2D vector `result`. Iterate through the hash map and move (`std::move` for performance) each gathered anagram group into `result`.

---

## Complexity Analysis

Let $N$ be the number of strings in the input array, and $M$ be the maximum length of a string.

* **Time Complexity:** $\mathcal{O}(N \cdot M \log M)$
  We iterate through all $N$ strings. For each string, sorting it takes $\mathcal{O}(M \log M)$ time. Hash map insertions and lookups take $\mathcal{O}(M)$ average time to hash the string key. Thus, the total time is dominated by the sorting phase: $\mathcal{O}(N \cdot M \log M)$.

* **Space Complexity:** $\mathcal{O}(N \cdot M)$
  In the worst-case scenario, where no two words are anagrams, the hash map will store every single word individually. The total space required to hold all elements inside the hash map scales linearly with the total number of characters across the input.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Pairwise Compare)** | $\mathcal{O}(N^2 \cdot M)$ | $\mathcal{O}(1)$ | Compares every string with every other string. Extremely slow for large inputs. |
| **Categorize by Frequency Count** | $\mathcal{O}(N \cdot M)$ | $\mathcal{O}(N \cdot M)$ | Replaces sorting with a fixed-size count array (e.g., 26 integers) converted to a string key. Faster asymptotically when $M$ is large, but might have higher constant overhead for short words. |