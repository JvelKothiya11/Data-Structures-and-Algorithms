# Gas Station

## Problem Statement
There are `n` gas stations along a circular route, where the amount of gas at the $i^{\text{th}}$ station is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from the $i^{\text{th}}$ station to its next $(i + 1)^{\text{th}}$ station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays `gas` and `cost`, return *the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return `-1`*. If there exists a solution, it is **guaranteed** to be **unique**.

---

## Key Insight / Intuition
This problem can be efficiently solved using a **Single-Pass Greedy Algorithm** based on two mathematical properties:

1. **Global Feasibility Guarantee:** If the total amount of gas available across all stations is greater than or equal to the total cost required ($\sum \text{gas}[i] \ge \sum \text{cost}[i]$), a valid starting point is guaranteed to exist.
2. **Local Reset Principle:** If starting from station $A$ allows us to reach station $B$, but we run out of gas trying to reach $B + 1$ (i.e., `currentBalance < 0`), then **no station between $A$ and $B$ can be a valid starting point**. Any intermediate station would start with zero initial gas reserves, making it perform even worse than starting at $A$ (which arrived at those intermediate stations with a non-negative fuel balance). Therefore, we can safely reset our candidate starting index to $B + 1$ and reset our running tank balance to `0`.

---

## Step-by-Step Approach
1. **Initialize State Trackers:**
   - `totalBalance = 0`: Tracks the net overall fuel across the entire circuit ($\sum (\text{gas}[i] - \text{cost}[i])$).
   - `currentBalance = 0`: Tracks the net accumulated fuel for the current candidate route segment.
   - `startIndex = 0`: Represents the current candidate starting gas station.
2. **Iterate Through Stations:** Loop through indices $i$ from `0` to $n - 1$:
   - Compute the net gain/loss at station $i$: $\text{balance} = \text{gas}[i] - \text{cost}[i]$.
   - Update both `totalBalance += balance` and `currentBalance += balance`.
3. **Handle Fuel Deficits (Greedy Reset):**
   - If `currentBalance < 0`, the current segment starting at `startIndex` cannot reach station $i + 1$.
   - Reset `currentBalance = 0` and update `startIndex = i + 1`.
4. **Final Verification:**
   - After completing the loop, if `totalBalance >= 0`, return `startIndex`.
   - Otherwise, if `totalBalance < 0`, it is mathematically impossible to complete the circuit from any station; return `-1`.

---

## Complexity Analysis

Let $N$ be the number of gas stations (the size of the `gas` and `cost` vectors).

* **Time Complexity:** $\mathcal{O}(N)$
  The algorithm iterates through the arrays exactly once. Inside the loop, all operations (arithmetic additions, comparisons, pointer shifts) execute in constant $\mathcal{O}(1)$ time, yielding a strictly linear runtime without redundant re-traversals.

* **Space Complexity:** $\mathcal{O}(1)$
  The operations take place entirely in-place. Memory consumption is completely constant as it relies only on a few integer accumulators (`totalBalance`, `currentBalance`, `startIndex`).

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Simulation** | $\mathcal{O}(N^2)$ | $\mathcal{O}(1)$ | Simulates starting from every index $i$ and driving around the circle step-by-step. Exceeds time limits for large inputs. |
| **Circular Array Extension** | $\mathcal{O}(N)$ | $\mathcal{O}(N)$ | Concatenates the array to simulate the circle explicitly. Adds unneeded memory overhead. |