# Pow(x, n)

## Problem Statement
Implement `pow(x, n)`, which calculates $x$ raised to the power $n$ ($x^n$). 

The input base `x` is a floating-point number (`double`), and the exponent `n` is an integer (`int`) which can be positive, negative, or zero.

---

## Key Insight / Intuition
A naive implementation multiplies $x$ by itself $n$ times, resulting in an inefficient $\mathcal{O}(n)$ time complexity. For large values of $n$ (e.g., $n = 2^{31}-1$), this will lead to a Time Limit Exceeded (TLE) error.

The optimal approach is **Exponentiation by Squaring** (Binary Exponentiation). The core insight relies on the property that we can halve the exponent at each step, reducing the number of multiplications down to a logarithmic scale. Instead of calculating $x^8$ as $x \times x \times x \times x \times x \times x \times x \times x$, we can calculate it as:
$$x^8 = (x^4)^2 = ((x^2)^2)^2$$

### Edge Case: Integer Overflow
In C++, the minimum value of a standard 32-bit signed integer is $-2,147,483,648$ (`INT_MIN`). If we simply negate `n` when it is negative to make it positive, converting `INT_MIN` to a positive value will cause an integer overflow because `INT_MAX` is only $2,147,483,647$. To handle this safely, we must cast `n` to a 64-bit integer (`long long`) before taking its absolute value.

---

## Mathematical Derivation
The recursive breakdown for computing $x^n$ (where $n \ge 0$) follows these rules:

1. **Base Case:**
   $$x^0 = 1$$

2. **Even Exponent:** If $n$ is even, the exponent can be perfectly halved.
   $$x^n = \left(x^{\frac{n}{2}}\right)^2$$

3. **Odd Exponent:** If $n$ is odd, halving $n$ via integer division discards the remainder of $1$. We compensate by multiplying the squared result by an extra factor of $x$.
   $$x^n = \left(x^{\frac{n}{2}}\right)^2 \times x$$

For negative exponents, we apply the algebraic identity:
$$x^{-n} = \frac{1}{x^n}$$

---

## Step-by-Step Approach
1. **Handle Exponent Bounds:** In `myPow`, cast `n` to a `long long` and compute its absolute value using `std::llabs` to securely manage `INT_MIN`.
2. **Recursive Helper Structure (`power`):**
   * **Base Case:** If `n == 0`, return `1.0`.
   * **Divide Step:** Recursively calculate `power(x, n / 2)` and store it in a variable named `half`. This guarantees that we make only **one** recursive call per level instead of two.
   * **Conquer Step:** Square the result: `result = half * half`.
   * **Adjust for Odds:** If `n` is even (`n % 2 == 0`), return `result`. If `n` is odd, return `result * x`.
3. **Invert for Negative Exponents:** If the original exponent `n` was negative, return `1.0 / result`; otherwise, return `result`.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(\log n)$
With every recursive call, the exponent $n$ is divided by $2$. The total number of recursive frames is bounded by the number of bits required to represent $n$, giving a logarithmic execution path.

### Space Complexity: $\mathcal{O}(\log n)$
The recursive execution uses system stack space proportional to the depth of the recursion tree, which is $\mathcal{O}(\log n)$ levels deep.

---

## Alternative Approaches

| Approach | Description | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Linear Brute Force** | Loop from $1$ to $n$, multiplying the result by $x$ at each step. | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| **Iterative Binary Exponentiation** | Processes bits of $n$ from right to left using a loop. Squares $x$ at each bit shift and multiplies into the result when a set bit (`1`) is encountered. | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ |