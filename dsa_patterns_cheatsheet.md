# DS&A Patterns — Tell → Strategy → Complexity

Match the problem's *tell* to a pattern. The complexity column is a giveaway in reverse: the target Big-O in the prompt often names the strategy.

---

## Reading complexity as a hint
| Prompt says / n size | It's hinting at |
|---|---|
| `O(1)` extra space required | In-place: two pointers, index math, or reuse the input array |
| `O(log n)` time | Binary search, or balanced-tree/heap ops |
| `O(n log n)` time | Sort first, then a linear pass — or a heap |
| `O(n)` time, one pass | Hash map/set, sliding window, prefix sums, Kadane |
| n ≤ ~20 | Exponential is fine → bitmask / subsets / backtracking |
| n ≤ ~500 | `O(n^2)` or `O(n^3)` DP is fine |
| n ≤ ~1e5–1e6 | Need `O(n)` or `O(n log n)` — quadratic will TLE |
| Answer is "count ways / min cost / longest" | Dynamic programming |
| "Kth largest / smallest", "top K" | Heap (size K) or quickselect |

---

## Array / String patterns

**Two pointers** — *tell:* sorted array, find a pair/triplet, or partition in place.
- Opposite ends closing in (2Sum on sorted, container-with-water), or slow/fast (dedup, cycle).
- Time `O(n)`, space `O(1)`.

**Sliding window** — *tell:* "longest/shortest subarray/substring satisfying X", contiguous.
- Expand right, shrink left when the window breaks the condition.
- Time `O(n)`, space `O(1)` or `O(k)` for a counter map.

**Prefix sums** — *tell:* many range-sum queries, or "subarray summing to K".
- Precompute `pre[i]`; range = `pre[r] - pre[l-1]`. With a hashmap, count subarrays = K.
- Build `O(n)`, query `O(1)`.

**Kadane** — *tell:* maximum subarray sum.
- Running sum, reset to 0 (or current) when it goes negative. `O(n)`.

**Binary search on the answer** — *tell:* "minimize the maximum / maximize the minimum", monotonic feasibility.
- Guess a value, check feasibility in `O(n)`, binary search the guess. `O(n log(range))`.

---

## Hashing patterns

**Frequency map** — *tell:* anagrams, counts, "seen before?", first unique.
- `unordered_map<T,int>` with `[x]++`. `O(n)`.

**Set for O(1) membership** — *tell:* dedup, "exists?", longest consecutive sequence.

---

## Stack / Monotonic

**Monotonic stack** — *tell:* "next greater/smaller element", "largest rectangle", "daily temperatures".
- Keep a stack that's increasing or decreasing; pop while the incoming element violates it. `O(n)`.

**Plain stack** — *tell:* matching brackets, expression eval, iterative DFS.

---

## Trees

**BFS (level order)** — *tell:* "level by level", shortest path in unweighted tree/graph.
- `queue`, process one level at a time. `O(n)`.

**DFS (recursion)** — *tell:* path sums, subtree properties, "all root-to-leaf".
- Recurse; return values up the call stack. `O(n)`, space `O(h)` for recursion.

**BST property** — *tell:* sorted-order needs → in-order traversal yields sorted sequence.

---

## Graphs

**BFS / DFS traversal** — *tell:* connected components, flood fill, reachability. `O(V + E)`.

**Dijkstra** — *tell:* shortest path, **non-negative** weights.
- `priority_queue<pair<dist,node>>` (min-heap). `O(E log V)`.

**Topological sort** — *tell:* ordering with dependencies / prerequisites, DAG.
- Kahn's (BFS on in-degree 0) or DFS post-order. `O(V + E)`.

**Union-Find (DSU)** — *tell:* "are these connected?", counting components, cycle detection in undirected, Kruskal.
- Path compression + union by rank → near `O(1)` amortized.

**Grid as graph** — *tell:* matrix with 4/8-directional movement. BFS/DFS over cells; directions array `{{0,1},{1,0},{0,-1},{-1,0}}`.

---

## Dynamic Programming (the rusty zone — lean here)

**How to spot DP:** optimal substructure + overlapping subproblems. Words: "count the number of ways", "min/max cost/length", "can you reach", "longest ___".

**Approach:** define the state (what varies), the transition (how a state builds from smaller ones), the base case, and the answer cell.

| Shape | Tell | State |
|---|---|---|
| 1D linear | "steps", "house robber", "decode ways" | `dp[i]` = best up to index i |
| Knapsack (0/1) | pick/skip items under a capacity | `dp[i][w]` |
| Unbounded knapsack | coins, unlimited reuse | `dp[amount]` |
| 2D grid | paths, min path sum, edit distance | `dp[i][j]` |
| Subsequence | LCS, LIS, palindromic subseq | `dp[i][j]` or `dp[i]` |
| Interval | "burst balloons", matrix chain | `dp[l][r]` |

- LIS has an `O(n log n)` version with `lower_bound` — worth knowing.
- Start top-down (recursion + memo) if the transition is clearer that way; convert to bottom-up if you need the speed.

---

## Backtracking

**Tell:** "generate all", permutations, combinations, subsets, N-queens, sudoku, word search. n is small.
- Choose → recurse → un-choose. Prune early. Often `O(2^n)` or `O(n!)` — fine because n is tiny.
