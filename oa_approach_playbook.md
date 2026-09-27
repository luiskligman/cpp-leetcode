# OA Approach Playbook — Triage → Template → Edge Cases

For a timed OA where the problems are harder than LeetCode-easy. Read top-to-bottom once; in the exam, use §1 to triage, §4 to paste, §5 before you submit.

---

## 1. The first 5 minutes (do this in order, every problem)

1. **Read the constraints before the story.** `n ≤ 1e5` and `n ≤ 20` are different problems. Note the *value* range too — that decides `int` vs `long long`.
2. **Write the brute force in your head** and say its complexity out loud. That's your baseline and your correctness oracle.
3. **Compute your budget** from §2. If brute force fits, *write brute force* — a correct `O(n^2)` beats a broken `O(n log n)`.
4. **Find the bottleneck** in the brute force ("for each i, I rescan" / "I re-sort" / "I recompute the max"). Name it — the bottleneck picks the tool:
   - rescanning for a *pair/condition* → two pointers, hash map
   - rescanning a *contiguous range* → sliding window, prefix sums
   - re-finding the *max/min* → heap, monotonic stack
   - re-searching a *sorted thing* → binary search
   - recomputing *overlapping subproblems* → DP / memo
   - re-walking *connectivity* → BFS/DFS/DSU
5. **Do one worked example by hand**, including the smallest one (`n = 0, 1`). This is where most "clever" ideas die.
6. **Decide the state/types now:** what's the answer type (`long long`?), what identifies an entity (id? price? index?), what are the tie-break rules?

> If you're stuck past ~8 minutes with no approach: write the brute force, get partial credit, move on. Come back with time left over.

---

## 2. Complexity budget (≈1e8 simple ops/sec, judges usually 1–2 s)

| n | What fits | Typical approach |
|---|---|---|
| ≤ 10 | `O(n!)` | permutations, brute force |
| ≤ 20–25 | `O(2^n)`, `O(2^n · n)` | subsets, bitmask DP |
| ≤ 100 | `O(n^3)` | Floyd–Warshall, interval DP |
| ≤ 1,000 | `O(n^2)` | 2D DP, all pairs |
| ≤ 5,000 | `O(n^2)` borderline | keep the inner loop trivial |
| ≤ 1e5 | `O(n log n)` | sort, heap, binary search, map |
| ≤ 1e6 | `O(n)` / `O(n log n)` w/ small constant | prefix sums, counting, hash map; **use fast I/O** |
| ≤ 1e9 | `O(log n)` or math | binary search on answer, closed form, digit DP |

- `unordered_map` has a fat constant. At `n = 1e6`, an `int` key → plain `vector<int>` of counts is several times faster.
- Recursion depth ~1e5+ risks stack overflow → iterative BFS/DFS with an explicit stack.

---

## 3. Signal → approach triage

### Arrays / numbers
| Signal in the prompt | Approach |
|---|---|
| "contiguous subarray" + longest/shortest/at most K | sliding window |
| "subarray sums to K" / many range-sum queries | prefix sums (+ hash map of prefixes) |
| sorted input, find pair/triplet | two pointers |
| "minimize the maximum" / "maximize the minimum" / "smallest capacity such that…" | **binary search on the answer** |
| "next greater / previous smaller", histogram rectangles | monotonic stack |
| "K-th largest", "top K", streaming best-N | heap of size K |
| "median of a stream" | two heaps |
| max/min after many updates at both ends of a window | monotonic deque |
| answer needs order statistics over a changing set | `multiset` + iterators |
| huge coordinate values, few distinct | coordinate compression |

### Strings
| Signal | Approach |
|---|---|
| anagram / permutation of | 26-slot count array (not a map) |
| palindrome | two pointers from the ends, or expand-around-center |
| "parse this command/line format" | `getline` + `stringstream` |
| prefix matching, many words | trie (or sort + `lower_bound` if one-shot) |
| substring search | `s.find`, or rolling hash if repeated |

### Graphs / grids
| Signal | Approach |
|---|---|
| shortest path, unweighted | BFS |
| shortest path, non-negative weights | Dijkstra |
| "are these connected", count groups, merging | DSU |
| prerequisites, ordering, cycle in a DAG | topological sort (Kahn) |
| flood fill, islands, regions | BFS/DFS over cells |
| all-pairs distance, `n ≤ 100–400` | Floyd–Warshall |

### Counting / optimizing
| Signal | Approach |
|---|---|
| "number of ways", "min cost to", "can you reach" | DP |
| "pick the best at each step and it's provably fine" | greedy — **justify the exchange argument or don't trust it** |
| intervals: merge / max overlap / max non-overlapping | sort + sweep (see §4.12) |
| "schedule tasks with times/priorities" | heap, or sweep over events |
| "simulate these operations in order" | simulation — get the data structure right, see §4.13–14 |
| `n ≤ 20`, "all combinations/assignments" | backtracking or bitmask DP |

### Harder-OA flavors worth expecting
- **Event-driven simulation:** a stream of timestamped commands you must process in order, with tie-break rules. → `priority_queue` keyed by `(time, seq)`, §4.14.
- **Order book / matching:** two price-ordered books, best price first, FIFO within a price. → `map<price, …, greater<>>` for bids, `map` for asks, §4.13.
- **Exact arithmetic:** prices/money. Keep everything in **integer ticks or cents**, never `double`.
- **Heavy input:** hundreds of thousands of lines → fast I/O block, and parse with `>>` not `getline`+`stoi` where you can.
- **Stated tie-breaks:** "earliest timestamp wins", "lowest id first". Encode them in the comparator immediately; they are where the hidden tests live.

---

## 4. Templates (all compiled and run)

### 4.0 Skeleton + I/O
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;

    return 0;
}
```
```cpp
// line-based commands: "BUY 100 50" / "CANCEL 7"
string line;
while (getline(cin, line)) {
    if (line.empty()) continue;
    stringstream ss(line);
    string cmd; ss >> cmd;
    if (cmd == "BUY")    { long long px, qty; ss >> px >> qty; /* ... */ }
    else if (cmd == "CANCEL") { int id; ss >> id; /* ... */ }
}
// after a >>, consume the rest of the line before getline: getline(cin, line);
// comma-separated: while (getline(ss, field, ',')) { ... }
```

### 4.1 Binary search on the answer
The workhorse for "minimize the max". Write `feasible()` first; it's the whole problem.
```cpp
// smallest cap such that v can be split into <= k chunks each summing <= cap
bool feasible(long long cap, const vector<int>& v, long long k) {
    long long chunks = 1, cur = 0;
    for (int x : v) {
        if (x > cap) return false;                 // single element doesn't fit
        if (cur + x > cap) { chunks++; cur = x; }
        else cur += x;
    }
    return chunks <= k;
}

long long lo = *max_element(v.begin(), v.end());   // tightest possible
long long hi = accumulate(v.begin(), v.end(), 0LL);
while (lo < hi) {
    long long mid = lo + (hi - lo) / 2;            // overflow-safe
    if (feasible(mid, v, k)) hi = mid;             // works -> try smaller
    else lo = mid + 1;
}
// lo == hi == answer
```
- Maximizing instead? `if (feasible(mid)) lo = mid; else hi = mid - 1;` with `mid = lo + (hi - lo + 1) / 2` — **the +1 prevents an infinite loop.**

### 4.2 Sliding window
```cpp
// variable: longest window with no repeated char
unordered_map<char,int> cnt;
int best = 0, l = 0;
for (int r = 0; r < (int)s.size(); r++) {
    cnt[s[r]]++;
    while (cnt[s[r]] > 1) { if (--cnt[s[l]] == 0) cnt.erase(s[l]); l++; }
    best = max(best, r - l + 1);
}
```
```cpp
// fixed size k: max window sum
long long sum = 0, best = LLONG_MIN;
for (int i = 0; i < (int)v.size(); i++) {
    sum += v[i];
    if (i >= k) sum -= v[i - k];            // drop the element leaving the window
    if (i >= k - 1) best = max(best, sum);  // only a full window counts
}
```
- "at most K distinct" → shrink while `cnt.size() > K`. "exactly K" → `atMost(K) - atMost(K-1)`.

### 4.3 Prefix sums
```cpp
// count subarrays summing to exactly k  (works with negatives)
unordered_map<long long,long long> seen{{0, 1}};   // the empty prefix — don't forget it
long long pre = 0, ans = 0;
for (int x : v) { pre += x; ans += seen[pre - k]; seen[pre]++; }
```
```cpp
// range sums: pre[i] = sum of first i elements
vector<long long> pre(n + 1, 0);
for (int i = 0; i < n; i++) pre[i+1] = pre[i] + v[i];
long long rangeSum = pre[r+1] - pre[l];            // inclusive [l, r]
```

### 4.4 Monotonic stack
```cpp
// next strictly greater element to the right (-1 if none)
vector<int> res(n, -1);
stack<int> st;                                      // indices; values decreasing
for (int i = 0; i < n; i++) {
    while (!st.empty() && v[st.top()] < v[i]) { res[st.top()] = v[i]; st.pop(); }
    st.push(i);
}
```
- Previous smaller → iterate the same way with `>` and read `st.top()` before pushing. Leftovers in the stack have no answer.

### 4.5 Two pointers
```cpp
int l = 0, r = (int)v.size() - 1;                   // v sorted
while (l < r) {
    long long s = (long long)v[l] + v[r];           // cast BEFORE adding
    if (s == target) return {l, r};
    if (s < target) l++; else r--;
}
```

### 4.6 Heaps — top K and running median
```cpp
// K largest: a MIN-heap of size K (the small one gets evicted)
priority_queue<int, vector<int>, greater<int>> pq;
for (int x : v) { pq.push(x); if ((int)pq.size() > k) pq.pop(); }
// pq.top() is now the k-th largest
```
```cpp
// running median: max-heap for the low half, min-heap for the high half
priority_queue<int> lo;                                  // smaller half
priority_queue<int, vector<int>, greater<int>> hi;        // larger half
void add(int x) {
    lo.push(x);
    hi.push(lo.top()); lo.pop();                         // funnel through
    if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
}
double median() {
    return lo.size() == hi.size() ? (lo.top() + hi.top()) / 2.0 : lo.top();
}
```

### 4.7 Dijkstra
```cpp
// adj[u] = {(v, w), ...}
const long long INF = LLONG_MAX / 4;                 // /4 so INF + w can't overflow
vector<long long> dist(n, INF);
priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
dist[src] = 0; pq.push({0, src});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;                       // stale entry — REQUIRED
    for (auto [v, w] : adj[u])
        if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
}
```
- Negative weights → Bellman-Ford, not this. All weights equal → plain BFS.

### 4.8 BFS on a grid
```cpp
int R = g.size(), C = g[0].size();
vector<vector<int>> dist(R, vector<int>(C, -1));
queue<pair<int,int>> q;
dist[sr][sc] = 0; q.push({sr, sc});
int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};            // 8-dir: add the 4 diagonals
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;   // bounds FIRST
        if (g[nr][nc] == '#' || dist[nr][nc] != -1) continue;   // wall / visited
        dist[nr][nc] = dist[r][c] + 1;
        q.push({nr, nc});
    }
}
```
- Mark visited **when you push**, not when you pop, or the queue explodes.

### 4.9 DSU (union-find)
```cpp
struct DSU {
    vector<int> p, sz;
    int comps;
    DSU(int n) : p(n), sz(n, 1), comps(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }   // path compression
    bool unite(int a, int b) {                       // false = already together
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; comps--;
        return true;
    }
};
```
- Always compare `find(a) == find(b)`, never `p[a] == p[b]`.

### 4.10 DP
```cpp
// 0/1 knapsack, rolling 1D — iterate capacity BACKWARDS so each item is used once
vector<long long> dp(cap + 1, 0);
for (int i = 0; i < (int)w.size(); i++)
    for (int c = cap; c >= w[i]; c--)
        dp[c] = max(dp[c], dp[c - w[i]] + val[i]);
// unbounded (coins, reuse allowed): iterate c FORWARDS instead
```
```cpp
// LIS in O(n log n)
vector<int> tails;
for (int x : v) {
    auto it = lower_bound(tails.begin(), tails.end(), x);   // upper_bound => non-decreasing
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}
int len = tails.size();          // tails is NOT the actual subsequence
```
```cpp
// top-down memo shape
vector<vector<long long>> memo(n, vector<long long>(m, -1));
function<long long(int,int)> go = [&](int i, int j) -> long long {
    if (/* base case */) return 0;
    long long& res = memo[i][j];
    if (res != -1) return res;
    return res = max(go(i+1, j), go(i, j+1) + 1);
};
```

### 4.11 Backtracking
```cpp
void rec(int i, vector<int>& cur, vector<vector<int>>& out) {
    if (i == n) { out.push_back(cur); return; }
    rec(i + 1, cur, out);            // skip
    cur.push_back(v[i]);
    rec(i + 1, cur, out);            // take
    cur.pop_back();                  // UN-CHOOSE — the bug is always here
}
```
- Permutations: loop `for j in 0..n-1`, skip `used[j]`, mark/unmark. Duplicates: sort, then `if (j > 0 && v[j] == v[j-1] && !used[j-1]) continue;`.

### 4.12 Intervals
```cpp
// merge overlapping
sort(iv.begin(), iv.end());                            // by start
vector<pair<int,int>> out;
for (auto& [s, e] : iv) {
    if (!out.empty() && s <= out.back().second) out.back().second = max(out.back().second, e);
    else out.push_back({s, e});
}
```
```cpp
// max concurrent overlap (sweep line)
vector<pair<int,int>> ev;
for (auto& [s, e] : iv) { ev.push_back({s, +1}); ev.push_back({e, -1}); }
sort(ev.begin(), ev.end());     // at equal time, -1 sorts first => touching ends don't overlap
int cur = 0, best = 0;
for (auto& [t, d] : ev) { cur += d; best = max(best, cur); }
```
```cpp
// most non-overlapping intervals (greedy): earliest END first
sort(iv.begin(), iv.end(), [](auto& a, auto& b){ return a.second < b.second; });
int cnt = 0, lastEnd = INT_MIN;
for (auto& [s, e] : iv) if (s >= lastEnd) { cnt++; lastEnd = e; }
```
- Decide once whether intervals are **closed** `[s,e]` or **half-open** `[s,e)` and make every comparison agree (`s <= last` vs `s < last`).

### 4.13 Order book / matching engine
```cpp
struct OrderBook {
    map<long long, long long, greater<long long>> bids;   // price -> qty, HIGHEST first
    map<long long, long long> asks;                       // price -> qty, LOWEST first

    long long addBuy(long long px, long long qty) {       // returns qty traded
        long long traded = 0;
        while (qty > 0 && !asks.empty() && asks.begin()->first <= px) {
            auto it = asks.begin();                       // best (cheapest) ask
            long long fill = min(qty, it->second);
            traded += fill; qty -= fill; it->second -= fill;
            if (it->second == 0) asks.erase(it);          // erase the emptied level
        }
        if (qty > 0) bids[px] += qty;                     // remainder rests on the book
        return traded;
    }
};
```
- Need **FIFO priority within a price**? Make the value a `deque<Order>` and fill from the front.
- Need **cancel by id**? Keep `unordered_map<int, iterator-or-key>` alongside so cancel is `O(1)`/`O(log n)`, not a scan.
- Best bid/ask = `bids.begin()` / `asks.begin()`. **Check `.empty()` first** — an empty book is test case #1.

### 4.14 Event-driven simulation
```cpp
struct Event {
    long long t; int id;
    bool operator>(const Event& o) const {                // min-heap needs >
        return t != o.t ? t > o.t : id > o.id;            // tie-break: lower id first
    }
};
priority_queue<Event, vector<Event>, greater<Event>> pq(init.begin(), init.end());
while (!pq.empty()) {
    Event e = pq.top(); pq.pop();
    // handle e, possibly pq.push({e.t + delay, ...});
}
```
- Simultaneous events **must** have a deterministic tie-break — add a sequence number if the prompt implies input order.

### 4.15 Custom ordering
```cpp
// sort: comparator returns "a strictly before b"
sort(os.begin(), os.end(), [](const Order& a, const Order& b) {
    return a.px != b.px ? a.px > b.px : a.t < b.t;        // price desc, then time asc
});

// priority_queue: the comparator is INVERTED vs sort (top = "last" by that order)
priority_queue<int, vector<int>, greater<int>> minHeap;
auto cmp = [](const Order& a, const Order& b){ return a.px < b.px; };  // top = highest px
priority_queue<Order, vector<Order>, decltype(cmp)> pq(cmp);
```
- A comparator must be **strict** (`<`, not `<=`) or `sort` can crash on equal elements.

### 4.16 Coordinate compression
```cpp
vector<long long> xs = all_values;
sort(xs.begin(), xs.end());
xs.erase(unique(xs.begin(), xs.end()), xs.end());
int idx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();   // x -> 0..m-1
```

---

## 5. Edge cases — run this list before you submit

### Universal (costs 30 seconds, catches most failures)
- [ ] **n = 0** (empty input) and **n = 1**. Does your loop body or `v[0]` still make sense?
- [ ] All elements identical. All distinct. Already sorted. Reverse sorted.
- [ ] **Negatives and zero** — especially in sums, products, and "reset when negative" logic.
- [ ] Duplicates where the problem implies uniqueness (a `set` would silently drop them).
- [ ] **Overflow:** does any sum/product exceed `2^31-1` (≈2.1e9)? `1e5` values of `1e5` already does. Use `long long`, and cast *before* multiplying: `(long long)a * b`.
- [ ] Off-by-one on every `[l, r]` vs `[l, r)` boundary you wrote.
- [ ] Output format exactly as specified: separators, trailing newline, `YES` vs `Yes`, no debug prints left.
- [ ] Answer type: does the problem want a count that overflows `int`, or a `double` with set precision? (`cout << fixed << setprecision(6)`.)
- [ ] Unreachable / impossible → what do you print? `-1`, `0`, `"IMPOSSIBLE"`?

### Structural
- [ ] `v.size()` is **unsigned**: `i < v.size() - 1` explodes on empty. Cast to `(int)`.
- [ ] `front()/back()/top()/*begin()` on an empty container is UB → guard with `.empty()`.
- [ ] `m[k]` **inserts** — silently grows a map and breaks later `.size()` counts.
- [ ] Iterator invalidated after `erase`/`push_back` inside a loop → use `it = c.erase(it)`.
- [ ] Recursion depth vs `n` (1e5 deep = stack overflow) → go iterative.
- [ ] Integer division truncates toward zero; `-7 / 2 == -3` and `-7 % 2 == -1`. For a positive modulo: `((a % m) + m) % m`.
- [ ] `double` equality. Compare with an epsilon, or stay in integers.

### Per pattern
| Pattern | The specific trap |
|---|---|
| Sliding window | forgetting to shrink; window never reaching size k; erasing a zero count from the map |
| Two pointers | input not actually sorted; `l < r` vs `l <= r`; overflow in `v[l] + v[r]` |
| Binary search | infinite loop from `lo = mid`; searching a non-monotonic predicate; bounds not covering the answer |
| Prefix sums | missing the `{0, 1}` seed; using `pre[r] - pre[l]` when you meant `pre[r+1] - pre[l]` |
| Monotonic stack | `<` vs `<=` when values are equal; leftovers in the stack need a default answer |
| Heap | default is a **max**-heap; `pop()` returns void; pushing before checking size K |
| BFS | marking visited on pop instead of push; starting cell not marked; multi-source (push them all first) |
| Dijkstra | skipping the stale check; negative weights; `INF` overflow on `d + w` |
| DSU | comparing parents instead of `find()`; forgetting to decrement the component count |
| DP | wrong loop direction for 0/1 vs unbounded; uninitialized base cases; memo sentinel (`-1`) that's a valid answer |
| Backtracking | no un-choose; duplicate branches on repeated inputs |
| Intervals | closed vs half-open at touching endpoints (`[1,5]` and `[5,8]`) |
| Simulation | undefined tie-break; processing input order instead of time order; not handling cancel-of-already-filled |
| Grid | bounds check after indexing instead of before; `R`/`C` swapped; `grid[0]` on an empty grid |

---

## 6. Last 10 minutes
1. Re-read the problem statement's output spec once, literally.
2. Run `n = 1` and the empty case by hand.
3. Scan every `int` that touches a sum or product → `long long`?
4. Delete debug output.
5. If a case still fails and time is short: submit the brute force for the small subtasks rather than nothing.
