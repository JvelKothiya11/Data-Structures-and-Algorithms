# Valid Anagram

## Problem Statement
Given two strings `s` and `t`, return `true` if `t` is an **anagram** of `s`, and `false` otherwise.

An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

## Key Insight / Intuition
Two strings are anagrams if and only if they have the exact same characters with the exact same frequencies. 

Instead of sorting both strings (which requires $O(n \log n)$ time), we can count character occurrences in linear time using a **Frequency Array** (acting as a fixed-size Hash Map). We increment the counts for characters in string `s` and decrement them for characters in string `t`. If at any point during the decrement step a character's count drops below zero, it means `t` contains more instances of that character than `s` does, immediately invalidating the anagram condition.

## Approach

1. **Size Verification**: First, check if `s.size() != t.size()`. If their lengths differ, they cannot be anagrams. Return `false` immediately.
2. **Frequency Mapping**: Initialize a fixed-size array `frequency` of size 256 (covering the extended ASCII character set) with all elements set to `0`.
3. **Populate Counts**: Loop through string `s`. For each character `ch`, increment its corresponding value in the frequency array (`++frequency[ch]`).
4. **Validate and Match**: Loop through string `t`. For each character `ch`, decrement its corresponding value in the frequency array (`--frequency[ch]`).
   * If the frequency falls below `0`, it indicates either a mismatch or an excess of character `ch` in `t`. Return `false`.
5. **Return**: If both loops complete successfully without flagging any negative values, return `true`.

> **C++ Best Practice Note**: The code uses `unsigned char` in the range-based loops. This ensures safe indexing into the `std::array` when dealing with potentially signed extended ASCII values, avoiding dangerous negative array index bugs.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Where $n$ is the length of the strings. The algorithm makes two independent passes over strings of length $n$, executing constant-time $O(1)$ array operations at each step.
* **Space Complexity:** $O(1)$  
  The `std::array` allocates a fixed size of 256 integers regardless of how large the input strings grow, consuming strictly constant auxiliary space.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Sorting** | $O(n \log n)$ | $O(1)$ or $O(n)$ | Sorts both strings and compares them character by character. Highly readable but computationally slower. |
| **Dynamic Hash Map** (`std::unordered_map`) | $O(n)$ | $O(k)$ | Good if the character set is sparse or non-ASCII (like Unicode/UTF-8). However, it introduces pointer and hashing overhead compared to a primitive array. |

> **Note**: $k$ represents the number of unique characters in the input strings.