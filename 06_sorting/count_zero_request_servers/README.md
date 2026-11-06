# Count Servers in a Time Window

## Problem Statement
You are given a total of `n` servers, a 2D integer array `logs` where each `logs[i] = [server_id, time]` indicates that a server received a request at a specific timestamp, an integer `x`, and an array of integers `queries`.

For each query time $q$ in `queries`, return *the number of servers that did **not** receive any requests during the time window* $[q - x, q]$. (Alternatively, depending on the variant, count the number of servers that *did* or *did not* receive requests within that time window).

---

## Key Insight / Intuition
Processing each query independently by scanning all logs would lead to an inefficient $\mathcal{O}(Q \times L)$ time complexity (where $Q$ is the number of queries and $L$ is the number of logs). 

We can optimize this significantly using **Offline Queries and a Two-Pointer Sliding Window**:
1. **Sort Queries:** If we process queries in increasing order of their timestamp values, the time window $[q - x, q]$ moves strictly forward. 
2. **Sort Logs by Timestamp:** Sorting logs by their timestamps allows us to use two pointers (`left` and `right`) to dynamically expand or shrink our active time window without redundant re-scans.
3. **Track Server Frequencies:** Maintain a `serverFrequency` array to count how many requests each server has received within the current window. A server is considered active if its frequency is greater than zero.

---

## Step-by-Step Approach
1. **Pair and Sort Queries:** Attach the original query index to each query value so we can restore the answer order later, then sort `queries` in ascending order.
2. **Pair and Sort Logs:** Transform `logs` into `[timestamp, serverId]` pairs and sort them chronologically by timestamp.
3. **Initialize Trackers:** 
   - `answer` vector initialized to size $Q$.
   - `serverFrequency` array of size $n + 1$ to track active request counts per server.
   - Pointers `left = 0` and `right = 0`, along with an `activeServers` counter.
4. **Process Each Query (Sliding Window):**
   - For each sorted query time $q$, define the window bounds as $[\text{queryTime} - x, \text{queryTime}]$.
   - **Expand Window (`right` pointer):** Advance `right` to include all logs with timestamps $\le q$, updating `serverFrequency` and incrementing `activeServers` when a server receives its first request in the window.
   - **Contract Window (`left` pointer):** Advance `left` to remove logs with timestamps strictly less than $\text{queryTime} - x$, decrementing frequencies and reducing `activeServers` when a server's request count drops to zero.
   - **Record Answer:** Compute the number of inactive servers ($n - \text{activeServers}$) and store it at the query's `originalIndex`.
5. **Return Result:** Return the fully populated `answer` vector.

---

## Complexity Analysis

Let $L$ be the number of logs and $Q$ be the number of queries.

* **Time Complexity:** $\mathcal{O}(Q \log Q + L \log L + Q + L)$
  - Sorting the queries takes $\mathcal{O}(Q \log Q)$ time.
  - Sorting the logs takes $\mathcal{O}(L \log L)$ time.
  - The two-pointer sliding window traverses each log at most once across all queries, taking $\mathcal{O}(Q + L)$ time.

* **Space Complexity:** $\mathcal{O}(Q + L + N)$
  - Requires auxiliary storage for the sorted query pairs, sorted log pairs, the server frequency-tracking array, and the final answer vector.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force (Per Query Scan)** | $\mathcal{O}(Q \times L)$ | $\mathcal{O}(1)$ | Scans all logs for every individual query. Extremely slow and will time out for large datasets. |