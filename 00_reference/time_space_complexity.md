# Time & Space Complexity Cheat Sheet

| Complexity | Typical Interpretation |
| ---------- | ---------------------- |
| O(1)       | Constant               |
| O(log n)   | Logarithmic            |
| O(n)       | Linear                 |
| O(n log n) | Linearithmic           |
| O(n²)      | Quadratic              |
| O(n³)      | Cubic                  |
| O(2ⁿ)      | Exponential            |
| O(n!)      | Factorial              |

---

## Constraint Guidelines

| Input Size | Preferred Complexity |
| ---------- | -------------------- |
| n ≤ 10     | O(n!)                |
| n ≤ 20     | O(2ⁿ)                |
| n ≤ 100    | O(n³)                |
| n ≤ 10³    | O(n²)                |
| n ≤ 10⁵    | O(n log n)           |
| n ≤ 10⁶    | O(n)                 |

---

## Space Complexity Notes

* Auxiliary arrays typically require O(n) space.
* Hash maps and hash sets usually require O(n) space.
* Recursive solutions require O(recursion depth) stack space.
* In-place algorithms generally target O(1) auxiliary space.
