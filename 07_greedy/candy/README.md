# Candy

## Problem Statement
There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:
* Each child must have at least one candy.
* Children with a higher rating get more candies than their neighbors.

Return *the minimum number of candies you need to have to distribute the candies to the children*.

---

## Key Insight / Intuition
A greedy two-pass approach solves this problem efficiently by decoupling the left and right neighbor constraints:
1. **Conflicting Constraints:** A child's candy count depends on both their left neighbor and right neighbor simultaneously. Trying to satisfy both directions in a single forward loop is difficult because changing a value can break the condition for the preceding or succeeding elements.
2. **Two-Pass Separation:** 
   - **Left-to-Right Pass:** Ensures that if a child has a higher rating than their *left* neighbor, they receive more candies than that left neighbor.
   - **Right-to-Left Pass:** Ensures that if a child has a higher rating than their *right* neighbor, they receive more candies than that right neighbor. By taking the maximum (`std::max`) between the existing candy count and `candies[i + 1] + 1`, we preserve the constraints satisfied from the left pass while enforcing the right-to-left constraints.

---

## Step-by-Step Approach
1. **Edge Case Check:** If the `ratings` vector is empty ($n = 0$), return `0` candies immediately.
2. **Initialize Candies Array:** Create a vector `candies` of size $n$, initialized with `1` (since every child must receive at least one candy).
3. **Left-to-Right Sweep:** Loop from index $i = 1$ to $n - 1$:
   - If `ratings[i] > ratings[i - 1]`, update `candies[i] = candies[i - 1] + 1`.
4. **Right-to-Left Sweep:** Loop backwards from index $i = n - 2$ down to $0$:
   - If `ratings[i] > ratings[i + 1]`, update `candies[i] = std::max(candies[i], candies[i + 1] + 1)`.
5. **Sum Total:** Accumulate all values in the `candies` vector and return the total sum.

---

## Complexity Analysis

Let $N$ be the number of children (the size of the `ratings` array).

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm performs three independent linear scans: one for the left-to-right pass, one for the right-to-left pass, and one to sum the elements. Total time scales linearly with $N$.

* **Space Complexity:** $\mathcal{O}(N)$
  Requires an auxiliary `candies` vector of size $N$ to store the candy distribution for each child.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force** | $\mathcal{O}(N^2)$ | $\mathcal{O}(N)$ | Repeatedly adjusts candy counts until no violations occur. Inefficient and slow for large inputs. |
| **Slope Counting (Constant Space)** | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | Tracks uphill, downhill, and flat slopes dynamically. Achieves optimal $\mathcal{O}(1)$ space at the expense of increased code complexity. |