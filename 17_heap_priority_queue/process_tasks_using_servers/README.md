# Process Tasks Using Servers

## Problem Statement
You are given two 0-indexed integer arrays, `servers` and `tasks`, of lengths `n` and `m` respectively. `servers[i]` is the weight of the $i^{\text{th}}$ server, and `tasks[j]` is the time needed to process the $j^{\text{th}}$ task.

Tasks are assigned sequentially from index `0` to `m - 1`. At second `j`, the $j^{\text{th}}$ task arrives and can be processed by any free server. If multiple servers are free, choose the server with the **minimum weight**. If there is a tie in weight, choose the server with the **minimum index**. If no servers are free, we must wait until the server that becomes free earliest finishes its work (breaking ties by minimum weight, then minimum index).

Return *an array of length `m` representing the indices of the servers that will process the tasks*.

---

## Key Insight / Intuition
This scheduling problem can be efficiently modeled using **two priority queues (min-heaps)** to maintain the state of our servers dynamically:
1. **Idle Servers Heap** (`idleServers`): Stores servers that are currently available. Ordered primarily by **server weight** (ascending), and secondarily by **server index** (ascending) to satisfy the tie-breaking rules.
2. **Busy Servers Heap** (`busyServers`): Stores servers that are currently processing tasks. Ordered by **free time** (ascending), and then by **weight** and **index** to handle ties correctly when multiple servers free up simultaneously.

As time advances from `0` to `m - 1`, we first release any busy servers whose completion time is less than or equal to the current time, moving them back into the idle heap. We then assign the incoming task to the best available server or fast-forward to the earliest finishing server if no idle servers exist.

---

## Step-by-Step Approach
1. **Initialize Priority Queues:**
   - Populate `idleServers` with all available servers represented as pairs of `{weight, index}` using `std::greater` to act as a min-heap.
   - Initialize `busyServers` as a min-heap to track active servers by `{freeTime, weight, serverIndex}`.
2. **Iterate Through Tasks:** For each task at `taskIndex` (acting as the current arrival time):
   - **Release Finished Servers:** While `busyServers` is not empty and the top server's `freeTime` is $\le \text{currentTime}$, pop it from `busyServers` and push it into `idleServers`.
   - **Assign Task:**
     - *Case 1 (Idle Server Available):* If `idleServers` is not empty, pick the top server (minimum weight, then minimum index), record its index in `assignment`, and push it into `busyServers` with an updated completion time of `currentTime + tasks[taskIndex]`.
     - *Case 2 (No Idle Servers):* If `idleServers` is empty, pop the server from `busyServers` that becomes free earliest. Record its index, and update its completion time by adding the new task duration (`freeTime + tasks[taskIndex]`) before pushing it back.
3. **Return Result:** Return the final `assignment` vector containing the server index for each task.

---

## Complexity Analysis

Let $N$ be the number of servers and $M$ be the number of tasks.

* **Time Complexity:** $\mathcal{O}((N + M) \log N)$
  - Initializing the idle server heap takes $\mathcal{O}(N \log N)$ time.
  - For each of the $M$ tasks, heap insertions and extractions (`push`, `pop`, `top`) take $\mathcal{O}(\log N)$ time. Since each server is pushed and popped at most once per task assignment, total runtime scales efficiently.

* **Space Complexity:** $\mathcal{O}(N + M)$
  - The priority queues (`idleServers` and `busyServers`) store up to $N$ servers combined.
  - The `assignment` vector stores $M$ output indices.

---

## Alternative Approaches

| Approach | Time Complexity | Space Complexity | Pros / Cons |
| :--- | :--- | :--- | :--- |
| **Brute Force Simulation** | $\mathcal{O}(M \times N)$ | $\mathcal{O}(N)$ | Scans all servers linearly for each task to find the best match. Slow and inefficient for large inputs ($N, M \le 2 \times 10^5$). |