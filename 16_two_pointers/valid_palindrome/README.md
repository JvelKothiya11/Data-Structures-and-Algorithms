# Valid Palindrome

## Problem Statement
A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

## Key Insight / Intuition
The most efficient way to validate a palindrome is by using the **Two-Pointer** technique. 

Instead of generating a brand new string that filters out invalid characters (which costs extra memory), we can scan the original string in-place from both ends simultaneously. We place a `left` pointer at the beginning and a `right` pointer at the end. We simply skip over any character that is not alphanumeric, and compare the valid characters by normalizing them to lowercase.

## Approach

1. **Initialize Pointers**: Place `left` at index `0` and `right` at index `s.size() - 1`.
2. **Two-Pointer Traversal**: Loop while `left < right`:
   * **Skip Left Non-Alphanumeric**: Advance the `left` pointer forward (`++left`) as long as `s[left]` is not an alphanumeric character (checked using `std::isalnum`). Ensure `left < right` bounds are maintained.
   * **Skip Right Non-Alphanumeric**: Move the `right` pointer backward (`--right`) as long as `s[right]` is not alphanumeric.
   * **Compare Characters**: Normalize both characters to lowercase using `std::tolower`. 
     * If they do not match, the string is not a palindrome. Return `false`.
   * **Step Inward**: If they match, increment `left` and decrement `right` to check the next inner pair.
3. **Return**: If the pointers meet or cross without any mismatch, return `true`.

> **C++ Best Practice Note**: When passing characters to functions from `<cctype>` like `std::isalnum` or `std::tolower`, it is critical to cast the character to `unsigned char`. This prevents undefined behavior when processing negative `char` values (such as extended ASCII or UTF-8 characters).

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  Although there are nested loops, each character in the string of length $n$ is visited at most once by either the `left` or `right` pointer. The total operations scale linearly with the length of the string.
* **Space Complexity:** $O(1)$  
  The check is performed completely in-place using only two scalar index markers, avoiding any extra string allocations.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Filtered Copy & Reverse** | $O(n)$ | $O(n)$ | Extracts alphanumeric characters into a new string, reverses it, and compares. Very simple to read, but inefficient due to data duplication. |