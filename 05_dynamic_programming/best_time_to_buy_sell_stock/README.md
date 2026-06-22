# Best Time to Buy and Sell Stock

## Problem Statement
You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`-th day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the future** to sell that stock. Return *the maximum profit you can achieve from this transaction*. If you cannot achieve any profit, return `0`.

---

## Key Insight / Intuition
The problem boils down to finding the maximum positive difference between two numbers in the array, with the constraint that the smaller number (buy price) must appear before the larger number (sell price).

Instead of comparing every single pair of days, we can traverse the array while dynamically tracking the lowest price seen so far (`bestBuy`). For every subsequent day, we calculate the potential profit if we were to sell at the current price (`prices[i] - bestBuy`) and update our maximum profit (`maxProfit`) accordingly.

---

## Step-by-Step Approach
1. **Initialize Tracking Variables:** 
   * `bestBuy`: Set to the first day's price (`prices[0]`), representing our initial candidate for the lowest purchase price.
   * `maxProfit`: Set to `0`, as the minimum possible profit we can make is nothing at all.
2. **Iterate Through Prices:** Loop through the price history starting from the second day (index `1`).
3. **Calculate Potential Profit:** For each day, check what the profit would be if we sold the stock today after buying it at `bestBuy`. Update `maxProfit` if this potential profit exceeds our previous maximum.
4. **Update Minimum Buy Price:** Update `bestBuy` to be the minimum between our current `bestBuy` and today's price. This ensures future days are compared against the absolute lowest price available before them.
5. **Return Result:** Once the iteration finishes, `maxProfit` will hold the maximum achievable profit.

---

## Complexity Analysis

### Time Complexity: $O(n)$
* **Explanation:** The algorithm makes a single linear scan through the `prices` array of size $n$. At each step, it performs basic comparison operations which take $O(1)$ constant time.

### Space Complexity: $O(1)$
* **Explanation:** The solution executes in-place and only requires two integer variables (`bestBuy` and `maxProfit`) to maintain state, utilizing zero auxiliary memory.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- | :--- |
| **Brute Force** | Use nested loops to check the profit for every possible buy and sell pair where $\mathrm{price\_buy} < \mathrm{price\_sell}$. | $O(n^2)$ | $O(1)$ | Simple to write, but hits a Time Limit Exceeded (TLE) exception for large datasets. |
| **Dynamic Programming** | Create a helper array where `min_so_far[i]` stores the minimum price up to day `i`, then find the max difference. | $O(n)$ | $O(n)$ | Achieves linear time complexity, but wastes unnecessary memory compared to the variable-optimized one-pass approach. |