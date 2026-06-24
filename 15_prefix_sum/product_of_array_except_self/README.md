# Product of Array Except Self

## Problem Statement
Given an integer array `nums`, return an array `result` such that `result[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer. You must write an algorithm that runs in $O(n)$ time and without using the division operation.

## Key Insight / Intuition
The product of all elements except `nums[i]` can be broken down into two components:
1. The product of all elements to the left of $i$ (**Prefix Product**).
2. The product of all elements to the right of $i$ (**Suffix Product**).

Instead of computing these products from scratch for every element (which takes $O(n^2)$ time), we can build them dynamically. To achieve $O(1)$ auxiliary space, we construct the prefix products directly inside the final output array, and then calculate the suffix products on the fly while traversing backward, multiplying them into the output array.

## Approach

1. **Initialize**: Create a `result` array of the same size as `nums`, initialized with `1`.
2. **Forward Pass (Prefix Product)**: Iterate through the array from left to right (starting from index 1). For each position, store the product of all previous elements:

$$\text{result}[i] = \text{result}[i - 1] \times \text{nums}[i - 1]$$

4. **Backward Pass (Suffix Product)**: Maintain a running variable `suffixProduct` initialized to `1`. Iterate through the array from right to left:
   * Multiply the current value in `result[i]` (which currently holds its prefix product) by `suffixProduct`.
   * Update the running `suffixProduct` by multiplying it with `nums[i]` to prepare it for the next element to the left.
5. **Return**: Return the populated `result` array.

## Mathematical Formulation
For any element at index $i$:

$$\text{result}[i] = \prod_{j=0}^{i-1} \text{nums}[j] \times \prod_{k=i+1}^{n-1} \text{nums}[k]$$

Where:
* Prefix component: $\prod_{j=0}^{i-1} \text{nums}[j]$ (calculated in the first loop)
* Suffix component: $\prod_{k=i+1}^{n-1} \text{nums}[k]$ (accumulated dynamically in the second loop)

## Complexity Analysis

* **Time Complexity:** $O(n)$  
  The algorithm performs exactly two sequential passes over the array of size $n$ (one forward, one backward). This yields a strictly linear time complexity.
* **Space Complexity:** $O(1)$  
  The output array `result` does not count toward the auxiliary space complexity according to problem conventions. The only extra memory used is a single scalar integer variable (`suffixProduct`), establishing constant space consumption.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $O(n^2)$ | $O(1)$ | Uses nested loops to calculate the product for every element. TLE (Time Limit Exceeded) for large arrays. |
| **Division Method** | $O(n)$ | $O(1)$ | Finds the total product of the array and divides it by `nums[i]`. **Fails if the array contains zeros**, and violates constraints. |
| **Two Separate Arrays** | $O(n)$ | $O(n)$ | Creates two independent arrays (`prefix` and `suffix`) and multiplies them. Highly intuitive but consumes extra space. |