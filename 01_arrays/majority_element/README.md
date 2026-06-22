# Majority Element

## Problem Statement
Given an array `nums` of size $n$, find the majority element. The majority element is the element that appears more than $\lfloor n / 2 \rfloor$ times. 

You may assume that the majority element always exists in the array.

---

## Key Insight / Intuition
The provided solution implements **Boyer-Moore Voting Algorithm**. 

The core idea is a process of elimination. If we pair up the majority element with any other distinct element, the majority element will always have remaining unmatched instances because it appears more than half the time ($> n/2$). 

By maintaining a `candidate` and a `count` net-balance, different elements effectively cancel each other out, leaving the true majority element standing at the end.

---

## Step-by-Step Approach
1. **Initialize Variables:** Start with a `candidate` variable to store the potential majority element and a `count` initialized to `0`.
2. **Iterate Through the Array:** Loop through each element `num` in the array:
   * **Update Candidate:** If `count` drops to `0`, it means all previous elements have neutralized each other. We establish the current `num` as our new `candidate`.
   * **Update Count:** If the current `num` matches the `candidate`, increment `count` by `1`. If it is different, decrement `count` by `1`.
3. **Return Result:** After a single pass through the array, the `candidate` variable will hold the majority element.

> **Note:** Since the problem guarantees that a majority element always exists, a second pass to verify the candidate's validity is unnecessary.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n)$
We traverse the array of size $n$ exactly once. Each element is processed in $\mathcal{O}(1)$ constant time.

### Space Complexity: $\mathcal{O}(1)$
The algorithm operates in-place, utilizing only two integer variables (`candidate` and `count`), achieving optimal auxiliary space complexity.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Brute Force** | Use nested loops to count the frequency of each element individually. | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |
| **Sorting** | Sort the array. The majority element will always occupy the middle index ($n/2$). | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ or $\mathcal{O}(n)$ depends on sort |
| **Hash Map** | Count frequencies using a hash map and return the key where value $> n/2$. | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Bit Manipulation** | Determine the majority bit (0 or 1) at each of the 32 bit positions. | $\mathcal{O}(32 \cdot n) \rightarrow \mathcal{O}(n)$ | $\mathcal{O}(1)$ |