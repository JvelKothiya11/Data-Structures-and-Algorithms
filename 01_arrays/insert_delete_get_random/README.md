# Insert Delete GetRandom O(1)

## Problem Statement
Implement the `RandomizedSet` class:
* `RandomizedSet()` Initializes the `RandomizedSet` object.
* `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not present, `false` otherwise.
* `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
* `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that each element must have the same probability of being returned when `getRandom` is invoked).

You must implement the functions of the class such that each function works in average $\mathcal{O}(1)$ time complexity.

---

## Key Insight / Intuition
To achieve $\mathcal{O}(1)$ time complexity for `insert`, `remove`, and `getRandom` simultaneously:
1. **Array (`std::vector`):** Essential for `getRandom` because we can index into a contiguous block of memory in $\mathcal{O}(1)$ time using a pseudo-random index. However, removing an arbitrary element from the middle of a vector takes $\mathcal{O}(N)$ time due to shifting.
2. **Hash Map (`std::unordered_map`):** Essential for checking existence (`insert` and `remove` lookups) in $\mathcal{O}(1)$ average time by mapping each value to its index in the vector.

**The Swap-and-Pop Trick for Removal:** 
To remove an element from the vector in $\mathcal{O}(1)$ time without shifting elements, we locate the element's index via the hash map, swap its value with the **last element** in the vector, update the hash map entry for that last element, and then call `pop_back()`. This bypasses expensive shifts entirely.

---

## Step-by-Step Approach
1. **Data Structures:** 
   - `std::vector<int> values`: Stores the actual elements sequentially to allow uniform random access.
   - `std::unordered_map<int, int> valueToIndex`: Maps each element value to its current index position within the `values` vector.
2. **Insertion (`insert(val)`):**
   - Check if `val` already exists in `valueToIndex` using `contains()`. If it does, return `false`.
   - Record the current size of `values` as the index for `val`.
   - Add `val` to the end of `values` via `push_back()` and update the hash map mapping. Return `true`.
3. **Removal (`remove(val)`):**
   - Check if `val` exists in `valueToIndex`. If not, return `false`.
   - Retrieve the index of the element to remove (`indexToRemove`) and fetch the last element of the vector (`lastValue`).
   - Overwrite the element at `indexToRemove` with `lastValue`.
   - Update the hash map so `lastValue` points to its new index (`indexToRemove`).
   - Pop the last element from `values` using `pop_back()` and erase `val` from the hash map. Return `true`.
4. **Random Access (`getRandom()`):**
   - Check if the set is empty; throw an exception if so.
   - Generate a pseudo-random index using `std::rand()` modulo the vector size, and return the element at that index in $\mathcal{O}(1)$ time.

---

## Complexity Analysis

Let $N$ be the number of elements currently stored in the `RandomizedSet`.

* **Time Complexity:** 
  * `insert`: $\mathcal{O}(1)$ average ($\mathcal{O}(N)$ worst-case due to hash map resizing).
  * `remove`: $\mathcal{O}(1)$ average ($\mathcal{O}(1)$ vector operations and hash map lookups/erasures).
  * `getRandom`: $\mathcal{O}(1)$ time complexity.
* **Space Complexity:** $\mathcal{O}(N)$
  Requires linear memory proportional to the number of stored elements to maintain both the hash map and the dynamic array.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Hash Set Only (`std::unordered_set`)** | $\mathcal{O}(1)$ insert/remove | $\mathcal{O}(N)$ | Fast inserts and deletes, but `getRandom` becomes $\mathcal{O}(N)$ because sets lack direct index access. |
| **Sorted Vector / Binary Search** | $\mathcal{O}(N)$ insert/remove | $\mathcal{O}(N)$ | Keeps elements sorted, but vector shifting makes insertions and deletions slow. |