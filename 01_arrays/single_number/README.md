# Single Number

## Problem Statement
Given a non-empty array of integers `nums`, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

---

## Key Insight / Intuition
The most optimal way to solve this problem within $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space is by leveraging the unique algebraic properties of the **bitwise XOR (`^`) operator**.

If we take the XOR of all numbers in the array, the duplicate pairs will neutralize each other and cancel out down to `0`. The only element left standing at the end will be the single number that does not have a pair.

---

## Mathematical Derivation
The bitwise XOR operator obeys three critical algebraic laws that make this approach work:

1. **Identity Property:** Any number XORed with zero remains unchanged.
   $$X \oplus 0 = X$$
2. **Self-Inverse Property:** Any number XORed with itself results in zero.
   $$X \oplus X = 0$$
3. **Commutative & Associative Properties:** The order in which elements are XORed does not matter.
   $$A \oplus B \oplus A = A \oplus A \oplus B = (A \oplus A) \oplus B = 0 \oplus B = B$$

### Working Example
Given the array `nums = [4, 1, 2, 1, 2]`:
$$\text{Result} = 4 \oplus 1 \oplus 2 \oplus 1 \oplus 2$$

Rearranging the terms using commutative properties:
$$\text{Result} = (1 \oplus 1) \oplus (2 \oplus 2) \oplus 4$$
$$\text{Result} = 0 \oplus 0 \oplus 4 = 4$$

---

## Step-by-Step Approach
1. **Initialize Accumulator:** Declare an integer variable `xorResult` and initialize it to `0`.
2. **Scan Array:** Run a single loop through the `nums` vector.
3. **Apply Bitwise XOR:** For each iteration, compute `xorResult ^= num`. 
4. **Return Answer:** Once the loop completes, return `xorResult`. All paired numbers have turned into `0`, leaving only the unique number stored in the variable.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n)$
The algorithm iterates through the array of size $n$ exactly once. The bitwise XOR operation takes $\mathcal{O}(1)$ constant time per element.

### Space Complexity: $\mathcal{O}(1)$
The solution runs purely in-place, relying only on a single integer variable (`xorResult`) regardless of the array's scale.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force** | Use nested loops to count frequencies or look for duplicates. | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |
| **Sorting** | Sort the array and check adjacent pairs. If `nums[i] != nums[i+1]`, then `nums[i]` is the unique item. | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ or $\mathcal{O}(n)$ |
| **Hash Map / Set** | Store frequencies in a hash map, or add/remove elements using a hash set. The remaining element in the set is the answer. | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Math (Set Sum)** | Use the equation: $2 \times \text{Sum(Unique Elements)} - \text{Sum(Array Elements)}$. | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ to store unique elements |