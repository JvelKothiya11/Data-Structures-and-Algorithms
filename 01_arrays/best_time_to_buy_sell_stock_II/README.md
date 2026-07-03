# Best Time to Buy and Sell Stock II

## Problem Statement
You are given an integer array `prices` where `prices[i]` is the price of a given stock on the $i^{\text{th}}$ day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any time. However, you can buy it and then immediately sell it on the **same day**.

Find and return *the **maximum** profit you can achieve*.

---

## Key Insight / Intuition
This problem can be optimally solved using a **Greedy Algorithm**. 

Since we can execute as many transactions as we want, we don't need to look ahead to find the absolute global minimum and maximum prices. Instead, we can simply capture **every single upward price movement**. 

If the price of the stock tomorrow is higher than the price today, we can simulate buying today and selling tomorrow to secure a positive `dailyProfit`. Summing up all consecutive positive day-to-day changes yields the exact same total profit as buying at the bottom of a valley and selling at the peak of a mountain.

---

## Step-by-Step Approach
1. **Initialize Profit Tracker:** Declare `totalProfit` initialized to `0`.
2. **Iterate Day-by-Day:** Run a loop from `day = 1` up to `size - 1` to compare each day's price with the previous day.
3. **Calculate Daily Delta:** Find the price difference between consecutive days:
   $$\text{dailyProfit} = \text{prices}[day] - \text{prices}[day - 1]$$
4. **Accumulate Gains:** If `dailyProfit > 0` (meaning the price increased), add this difference directly to `totalProfit`. If the price dropped or stayed the same, ignore it.
5. **Return Result:** Once the array is fully traversed, return `totalProfit`.

---

## Complexity Analysis

Let $N$ be the number of days (the size of the `prices` vector).

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm iterates through the array exactly once, checking adjacent elements. Each comparison and addition takes $\mathcal{O}(1)$ constant time, resulting in a strictly linear runtime.

* **Space Complexity:** $\mathcal{O}(1)$
  The calculations are done entirely in place. The solution only uses a few primitive integer variables (`totalProfit`, `dailyProfit`, `day`) regardless of how large the input array scales.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Recursion)** | $\mathcal{O}(2^N)$ | $\mathcal{O}(N)$ | Tries every possible combination of buying and selling. Will quickly result in Time Limit Exceeded (TLE) for large inputs. |
| **Peak-Valley Approach** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Explicitly looks for the next local valley to buy and the next local peak to sell. Achieves identical performance but involves more complex loop syntax. |