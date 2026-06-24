# Longest Substring Without Repeating Characters

## Problem Statement
Given a string `s`, find the length of the **longest substring** without repeating characters. A substring is a contiguous sequence of characters within a string.

## Key Insight / Intuition
The problem can be efficiently solved using the **Sliding Window** technique with an optimized **Two-Pointer** approach. 

Instead of checking all possible substrings, we maintain a dynamic window `[left, right]` that contains only unique characters. As we expand the window by moving the `right` pointer, if we encounter a character that has already been seen inside the current window, we don't need to shrink the window one step at a time. Instead, we can immediately jump the `left` pointer to the position right after the last known occurrence of that duplicate character.

## Approach

1. **Direct Access Map**: Initialize an array/vector `lastSeen` of size 256 (covering all ASCII characters) with `-1` to keep track of the most recent index where each character appeared.
2. **Expand the Window**: Loop through the string with a pointer `right` from `0` to `s.size() - 1`.
3. **Update Left Bound**: For each character `s[right]`:
   * Check its last seen index in `lastSeen`. 
   * If it was seen within or after the current `left` boundary, update `left` to `lastSeen[s[right]] + 1`. We use `std::max` to ensure `left` never moves backward.
4. **Calculate Length**: The current valid window size is $(right - left + 1)$. Update `maxLength` if this window is larger than the previous maximum.
5. **Record Position**: Update `lastSeen[s[right]]` to the current `right` index.
6. **Return**: Once the loop finishes, `maxLength` holds the final answer.

## Mathematical Formulation
The length of a substring bounded by indices `left` and `right` (inclusive) is calculated as:

$$\text{Length} = \text{right} - \text{left} + 1$$

When a repeating character is found at index `right`, its previous index is $j = \text{lastSeen}[s[\text{right}]]$. The new left boundary is updated using:

$$\text{left}_{new} = \max(\text{left}_{old}, j + 1)$$

This guarantees that the window remains valid in $O(1)$ time without needing a nested loop to shrink the window incrementally.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  The `right` pointer traverses the string of length $n$ exactly once. Inside the loop, all lookups and updates in the `lastSeen` array happen in $O(1)$ time.
* **Space Complexity:** $O(1)$  
  The `lastSeen` array has a fixed size of 256 (the ASCII alphabet size), which is constant space and independent of the input string length $n$.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $O(n^3)$ | $O(\min(n, m))$ | Checks every possible substring and verifies uniqueness. Extremely inefficient for long strings. |
| **Sliding Window (Set)** | $O(2n) = O(n)$ | $O(\min(n, m))$ | Uses a Hash Set to track characters. In the worst case, each character is visited twice (once by `right`, once by `left`). |

> **Note**: $m$ represents the size of the character set (alphabet).