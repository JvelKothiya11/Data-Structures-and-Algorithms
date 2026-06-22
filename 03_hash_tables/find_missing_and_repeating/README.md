# Find Missing and Repeated Values

## Problem Statement
Given a 0-indexed 2D integer grid of size $n \times n$ containing all integers from $1$ to $n^2$ except for one number that appears twice (the repeated value) and one number that is completely missing (the missing value). 

The goal is to find and return a 1D vector containing the **repeated** and the **missing** values in that order.

---

## Key Insight / Intuition
This solution leverages basic algebraic equations derived from the math properties of consecutive numbers. Instead of tracking frequencies using a hash map or sorting the numbers, we can figure out the identities of both numbers by comparing:
1. The **actual sum** vs. the **expected sum** of integers from $1$ to $N$ (where $N = n^2$).
2. The **actual sum of squares** vs. the **expected sum of squares** of integers from $1$ to $N$.

By setting up a system of linear equations with the two differences, we can isolate and solve for both the repeated value ($A$) and the missing value ($B$) in optimal time without any extra space.

---

## Mathematical Derivation
Let $A$ be the repeated number and $B$ be the missing number. Let $N = n^2$.

### 1. Linear Difference Equation
The expected sum of numbers from $1$ to $N$ is given by:
$$S_{\text{expected}} = \frac{N(N + 1)}{2}$$

The difference between the actual grid sum ($S_{\text{actual}}$) and the expected sum yields our first equation:
$$\text{diff} = S_{\text{actual}} - S_{\text{expected}} = A - B$$

### 2. Quadratic Difference Equation
The expected sum of squares from $1$ to $N$ is given by:
$$S^2_{\text{expected}} = \frac{N(N + 1)(2N + 1)}{6}$$

The difference between the actual grid sum of squares ($S^2_{\text{actual}}$) and the expected sum of squares yields:
$$\mathrm{sq\_diff} = S^2_{\mathrm{actual}} - S^2_{\text{expected}} = A^2 - B^2$$

Using the algebraic identity $A^2 - B^2 = (A - B)(A + B)$, we can substitute $\text{diff} = A - B$:
$$\mathrm{sq\_diff} = \mathrm{diff} \times (A + B)$$
$$\text{sum} = A + B = \frac{\mathrm{sq\_diff}}{\text{diff}}$$

### 3. Solving for $A$ and $B$
Now we have a simple system of two linear equations:
1. $A - B = \text{diff}$
2. $A + B = \text{sum}$

Adding the equations isolates $A$ (Repeated):
$$2A = \text{sum} + \text{diff} \implies A = \frac{\text{sum} + \text{diff}}{2}$$

Subtracting the equations isolates $B$ (Missing):
$$2B = \text{sum} - \text{diff} \implies B = \frac{\text{sum} - \text{diff}}{2}$$

---

## Step-by-Step Approach
1. **Initialize Dimensions:** Calculate the total elements $N = n \times n$.
2. **Compute Grid Metrics:** Run a nested loop through the 2D grid to track the running total of `current_sum` and `current_sq_sum`. Use `1LL` casting to prevent integer overflow during square calculation.
3. **Compute Ideal Metrics:** Use the mathematical formulas to find `expected_sum` and `expected_sq_sum`.
4. **Calculate Differences:** Establish the values for `diff` ($A - B$) and `sq_diff` ($A^2 - B^2$).
5. **Evaluate Combinations:** Compute `sum` ($A + B$) by dividing `sq_diff` by `diff`.
6. **Extract Results:** Compute the final values of $A$ and $B$ using the isolated equations and return them.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n^2)$
We must visit every cell in the $n \times n$ grid exactly once to accumulate the actual sums. All subsequent mathematical calculations execute in $\mathcal{O}(1)$ time.

### Space Complexity: $\mathcal{O}(1)$
The algorithm works entirely with mathematical constants and variables (`current_sum`, `current_sq_sum`, etc.) without utilizing dynamic tracking allocations like hash sets or arrays.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Frequency Array / Hash Map** | Count frequencies of each number from $1$ to $N$. Check which entry equals `2` and which equals `0`. | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ |
| **Sorting** | Flatten the grid into a 1D array of size $n^2$, sort it, and compare adjacent elements to spot duplicates and gaps. | $\mathcal{O}(n^2 \log(n^2))$ | $\mathcal{O}(n^2)$ for copying |
| **Bit Manipulation (XOR)** | XOR all grid elements alongside all numbers from $1$ to $N$. Isolate the missing and repeated values via the lowest set bit. | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |