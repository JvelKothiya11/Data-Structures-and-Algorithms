# Subarray Sum Equals K

## Problem Statement
Given an array of integers `nums` and an integer `k`, return the total number of subarrays whose sum equals to `k`. A subarray is a contiguous non-empty sequence of elements within an array.

## Key Insight / Intuition
A brute force approach checks all possible subarrays, which is inefficient. Instead, we can optimize this using **Prefix Sums** combined with a **Hash Map**.

Let $\text{prefixSum}[i]$ be the sum of elements from index `0` to `i`. The sum of a subarray spanning from index `j + 1` to `i` can be calculated as:

$$\text{Subarray Sum}(j+1 \dots i) = \text{prefixSum}[i] - \text{prefixSum}[j]$$

We want this subarray sum to equal $k$:

$$\text{prefixSum}[i] - \text{prefixSum}[j] = k \implies \text{prefixSum}[j] = \text{prefixSum}[i] - k$$

As we iterate through the array and compute the running `prefixSum` (acting as $\text{prefixSum}[i]$), we can check a hash map to see how many times a prefix sum equal to $(\text{prefixSum} - k)$ has occurred in the past. If it exists, it means valid subarrays ending at the current index exist, and we add their frequency to our total count.

## Approach

1. **Initialize Map**: Create a hash map `prefixCount` to store the frequency of each prefix sum encountered. Initialize it with `prefixCount[0] = 1` because a prefix sum of `0` has implicitly occurred once before we even look at the first element (handling subarrays starting from index 0).
2. **Traverse and Accumulate**: Maintain a running `prefixSum` and loop through each `value` in `nums`.
3. **Check for Target Difference**: At each element, calculate the required previous prefix sum: `prefixSum - k`. 
   * Look up this value in `prefixCount`. If found, add its recorded frequency to `subarrayCount`.
4. **Update Map**: Record the current running `prefixSum` into `prefixCount` by incrementing its frequency by 1.
5. **Return**: Return the accumulated `subarrayCount`.

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  The algorithm iterates through the array of size $n$ exactly once. Inside the loop, looking up and inserting keys into the `std::unordered_map` takes $O(1)$ on average. Thus, the total time complexity is linear.
* **Space Complexity:** $O(n)$  
  In the worst-case scenario (e.g., all elements are positive or distinct), every prefix sum calculated will be unique. The hash map will store up to $n$ distinct key-value pairs, leading to linear space overhead.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Three Loops)** | $O(n^3)$ | $O(1)$ | Checks every pair of indices and computes the sum via a nested loop. Inefficient. |
| **Optimized Cumulative Sum** | $O(n^2)$ | $O(1)$ | Generates subarrays using two pointers, adding elements on the fly to track the sum. Avoids the third loop but still too slow for large inputs. |
| **Sliding Window (Two Pointer)** | $O(n)$ | $O(1)$ | Only works if **all elements are non-negative**. Fails when negative numbers are introduced since the window boundaries cannot expand/shrink monotonically. |