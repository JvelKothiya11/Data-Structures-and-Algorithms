# Maximum Subarray (Kadane's Algorithm)

## Problem Statement
Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return *its sum*.

---

## Key Insight / Intuition
The problem can be solved efficiently using **Kadane's Algorithm**, which is a form of dynamic programming. 

The core intuition is to iterate through the array and make a local choice at each element: Is it better to extend the existing subarray sum, or start a brand new subarray from the current element? 

Mathematically, at any index $i$, the maximum subarray sum ending at that position is defined by the recurrence relation:

$$\text{currentSum}[i] = \max(\text{nums}[i], \text{currentSum}[i-1] + \text{nums}[i])$$

Instead of maintaining an entire array to store these local maximums, we only need the global maximum (`maxSum`) and the maximum ending at the immediately preceding position (`currentSum`). This reduces our space tracking down to a constant number of variables.

---

## Step-by-Step Approach
1. **Initialize State:** Track two variables, `maxSum` and `currentSum`, both initialized to the value of the first element (`nums[0]`).
2. **Iterate Through the Array:** Loop through the array starting from the second element (index `1`).
3. **Local Optimization:** For each element, update `currentSum` by choosing the maximum between:
   * The current element itself (starting a new subarray).
   * The current element added to the previous `currentSum` (extending the existing subarray).
4. **Global Optimization:** Update `maxSum` if the newly calculated `currentSum` is greater than the current `maxSum`.
5. **Return Result:** Once the loop concludes, `maxSum` holds the highest contiguous sum found.

---

## Complexity Analysis

### Time Complexity: $O(n)$
* **Explanation:** The algorithm makes a single pass through the array of size $n$, performing constant-time operations $O(1)$ at each step.

### Space Complexity: $O(1)$
* **Explanation:** No auxiliary data structures are used. The state is maintained purely using two primitive integer variables, achieving constant space complexity.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- | :--- |
| **Brute Force** | Check the sum of every possible contiguous subarray using nested loops. | $O(n^2)$ | $O(1)$ | Easy to conceive but will result in a Time Limit Exceeded (TLE) on large arrays. |
| **Divide and Conquer** | Split the array into two halves, find the max subarray of the left, right, and crossing parts recursively. | $O(n \log n)$ | $O(\log n)$ | Good showcase of recursion/tree logic, but less optimal in both time and space compared to Kadane's. |