# STL Containers & Algorithms — Signal → Structure Cheat Sheet

Glance-only reference. Left-to-right: **when you reach for it → how to declare/use it → the syntax you always forget → the gotcha**.

---

## Sequence Containers

### `vector<T>` — your default array
**Use when:** you need a dynamic array, random access, mostly push/pop at the back.
```cpp
vector<int> v;                 v.push_back(x);
vector<int> v(n, 0);           // n elements, all 0
v[i];          // int& — no bounds check
v.at(i);       // int& — throws out_of_range if i is bad
v.front();     // int& — first element (UB if empty)
v.back();      // int& — last element (UB if empty)
v.size();      // size_t (unsigned!) — use (int)v.size() in math
v.empty();     // bool
v.pop_back();  // void — doesn't return the element
v.clear();     // void

auto it = find(v.begin(), v.end(), x);   // iterator, v.end() if not found
if (it != v.end()) { *it; int idx = it - v.begin(); }   // value, index

for (int i = 0; i < (int)v.size(); i++) v[i];   // by index
for (auto& x : v) {...}                          // by reference (can modify)
sort(v.begin(), v.end());
```
- Access `O(1)`, push_back amortized `O(1)`, insert/erase middle `O(n)`.
- **Gotcha:** `v.reserve(n)` before a known number of push_backs to avoid reallocations. Erasing invalidates iterators/pointers from that point on.

### `deque<T>` — double-ended vector
**Use when:** you push/pop at **both ends** (sliding window, BFS-ish queues).
```cpp
deque<int> d;   d.push_front(x); d.push_back(y);
d.front();      // int& — first
d.back();       // int& — last
d[i];           // int& — random access ok
d.pop_front();  d.pop_back();    // void — read front()/back() first
```
- Both ends `O(1)`, random access `O(1)` but slower constant than vector.
- **Gotcha:** no contiguous memory — don't treat `&d[0]` like a C array.

### `list<T>` — doubly linked list
**Use when:** tons of insert/erase in the **middle** and you hold iterators to spots.
```cpp
list<int> l;  l.push_back(x);  auto it = l.begin();  l.erase(it);
```
- Insert/erase at a known iterator `O(1)`; **no random access**.
- **Gotcha:** rarely the answer on OAs. Usually `vector` or `deque` wins on cache behavior. Reach for it only when the problem screams "splice/erase mid-list repeatedly."

### `array<T, N>` — fixed-size stack array
**Use when:** compile-time fixed size, want STL interface.
```cpp
array<int, 5> a = {1,2,3,4,5};   a.size();  a[i];
```

---

## Container Adapters

### `stack<T>` — LIFO
**Use when:** matching/nesting (parens, monotonic stack, DFS iterative, undo).
```cpp
stack<int> s;  s.push(x);
s.top();       // int& — last pushed (UB if empty)
s.pop();       // void — removes top, doesn't return it
s.size();  s.empty();
// can't iterate/index — to see contents, copy and drain the copy:
auto tmp = s;  while (!tmp.empty()) { cout << tmp.top() << ' '; tmp.pop(); }
```
- **Gotcha:** `pop()` returns **void**. Read `top()` first, then `pop()`.

### `queue<T>` — FIFO
**Use when:** BFS, order-preserving processing.
```cpp
queue<int> q;  q.push(x);
q.front();     // int& — oldest (next to pop)
q.back();      // int& — newest
q.pop();       // void — removes front
q.size();  q.empty();
// BFS: int cur = q.front(); q.pop();
```
- **Gotcha:** same as stack — `pop()` is void; grab `front()` first.

### `priority_queue<T>` — heap
**Use when:** you repeatedly need the **best/largest** (or smallest) element. Dijkstra, top-K, merge-K, scheduling.
```cpp
priority_queue<int> pq;                       // MAX-heap (default)
priority_queue<int, vector<int>, greater<int>> pq;  // MIN-heap
pq.push(x);
pq.top();      // const int& — the best element (read-only)
pq.pop();      // void — removes top
pq.size();  pq.empty();
// pair: pq.top().first / .second — or: auto [d, node] = pq.top();
```
- push/pop `O(log n)`, top `O(1)`.
- **Gotcha:** default is a **max**-heap. For a min-heap use `greater<int>`, or push negated values. For pairs, it orders by `.first` then `.second`.

---

## Associative (ordered, tree-based) — `O(log n)`

### `map<K,V>` / `set<K>`
**Use when:** you need keys **kept sorted**, range queries, or floor/ceiling lookups.
```cpp
map<int,int> m;   m[k] = v;
m[k];            // int& — INSERTS 0 if k missing
m.at(k);         // int& — throws out_of_range if k missing
m.count(k);      // 0 or 1 — check without inserting
auto it = m.find(k);             // iterator, m.end() if missing
if (it != m.end()) { it->first; it->second; }   // key, value
m.begin()->first;    // smallest key
m.rbegin()->first;   // largest key
m.erase(k);          // removes key
for (auto& [k, v] : m) {...}     // sorted key order; v writable, k const

set<int> st;  st.insert(x);
st.count(x);     // 0 or 1
st.find(x);      // iterator, st.end() if missing
*st.begin();     // smallest
*st.rbegin();    // largest
st.erase(x);
auto it = st.lower_bound(x);   // iterator to first >= x (st.end() if none)
auto it = st.upper_bound(x);   // iterator to first >  x
if (it != st.begin()) *prev(it);   // largest <= x (after upper_bound)
```
- All ops `O(log n)`. Iteration is in sorted order.
- **Gotcha:** `m[k]` **inserts a default (0)** if `k` is absent — use `.count()`/`.find()`/`.contains()` (C++20) to test membership without inserting. `multiset`/`multimap` allow duplicate keys.

---

## Unordered (hash-based) — `O(1)` average

### `unordered_map<K,V>` / `unordered_set<K>`
**Use when:** fast lookup by key, **order doesn't matter**. Frequency counts, seen-sets, memoization.
```cpp
unordered_map<int,int> cnt;   cnt[x]++;      // counter pattern, auto-0
cnt[k];          // int& — INSERTS 0 if k missing
cnt.at(k);       // int& — throws out_of_range if k missing
cnt.count(k);    // 0 or 1 — check without inserting
auto it = cnt.find(k);           // iterator, cnt.end() if missing
if (it != cnt.end()) { it->first; it->second; }   // key, value
cnt.erase(k);
cnt.size();      // number of distinct keys
for (auto& [k, v] : cnt) {...}   // random order

unordered_set<int> seen;  seen.insert(x);
seen.count(x);   // 0 or 1
seen.find(x);    // iterator, seen.end() if missing
seen.erase(x);
for (int x : seen) {...}         // random order
```
- Average `O(1)`, worst case `O(n)` on hash collisions.
- **Gotcha:** no ordering. `cnt[x]++` is the built-in `defaultdict(int)`. Can't hash a `pair`/`vector` without a custom hash — for pair keys either use `map` or encode into one number (`a*BIG + b`).

---

## Common Algorithms (`<algorithm>`, `<numeric>`)

```cpp
sort(v.begin(), v.end());                       // ascending, O(n log n)
sort(v.begin(), v.end(), greater<int>());       // descending
sort(v.begin(), v.end(), [](auto&a, auto&b){ return a.second < b.second; });

reverse(v.begin(), v.end());
lower_bound(v.begin(), v.end(), x);  // first >= x  (v must be sorted)
upper_bound(v.begin(), v.end(), x);  // first > x
binary_search(v.begin(), v.end(), x);           // bool

max_element(v.begin(), v.end());   // returns iterator; *it for value
min_element(v.begin(), v.end());
accumulate(v.begin(), v.end(), 0LL);            // sum — use 0LL to avoid overflow
count(v.begin(), v.end(), x);
unique(v.begin(), v.end());        // needs sorted first; erase leftovers
v.erase(unique(v.begin(), v.end()), v.end());   // dedup idiom

fill(v.begin(), v.end(), 0);
__gcd(a, b);
```
- **Gotcha:** `lower_bound`/`binary_search`/`unique` all assume the range is **already sorted**. `accumulate`'s init value sets the type — pass `0LL` for long long sums.

---

## Quick "which container?" decision list
- Random access + push back → **vector**
- Push/pop both ends → **deque**
- LIFO → **stack** · FIFO → **queue** · best-first → **priority_queue**
- Lookup by key, order irrelevant → **unordered_map/set**
- Keys must stay sorted / need floor-ceiling / range → **map/set**
- Count frequencies → **unordered_map<T,int>** with `[x]++`
