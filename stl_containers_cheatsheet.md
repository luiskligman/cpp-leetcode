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
v.size();      // size_t (unsigned!) — # of elements; use (int)v.size() in math
v.empty();     // bool — same as v.size() == 0
int R = g.size(), C = g[0].size();   // 2D: rows, cols (guard g.empty() first)
v.pop_back();  // void — doesn't return the element
v.clear();     // void — size becomes 0

v.insert(v.begin()+i, x);            // iterator to the new element; O(n), shifts the rest
v.insert(v.end(), {7,8});            // insert a list/range at a position
v.erase(v.begin()+i);                // iterator to the NEXT element; O(n)
v.erase(v.begin()+a, v.begin()+b);   // erase the range [a, b)
v.resize(n);        // void — grow (new slots = 0) or shrink to exactly n
v.resize(n, -1);    // void — grow filling with -1
v.assign(n, 0);     // void — wipe and refill with n copies of 0
v.reserve(n);       // void — pre-allocate capacity, no size change
v.emplace_back(x);  // like push_back but builds in place (pairs/structs)
swap(v, w);         // void — O(1) swap of two vectors
v == w;             // bool — elementwise compare (also <, for sorting vectors)

auto it = find(v.begin(), v.end(), x);   // iterator, v.end() if not found
if (it != v.end()) { *it; int idx = it - v.begin(); }   // value, index

for (int i = 0; i < (int)v.size(); i++) v[i];   // by index
for (auto& x : v) {...}                          // by reference (can modify)
sort(v.begin(), v.end());
```
- Access `O(1)`, push_back amortized `O(1)`, insert/erase middle `O(n)`.
- **Gotcha:** `v.reserve(n)` before a known number of push_backs to avoid reallocations. Erasing invalidates iterators/pointers from that point on.

### `string` — a vector of chars (+ extras)
**Use when:** any text problem — palindromes, anagrams, parsing, building output.
```cpp
string s = "hello world";   string t(n, 'a');   // n copies of 'a'
s[i];            // char& — no bounds check
s.at(i);         // char& — throws out_of_range if i is bad
s.front();       // char& — first (UB if empty)
s.back();        // char& — last  (UB if empty)
s.size();        // size_t (unsigned!) — # of chars
s.length();      // size_t — identical to s.size(), just a different name
s.empty();       // bool — same as s.size() == 0
s.substr(pos, len);   // string — COPY, len chars from pos ("world" = s.substr(6, 5))
s.substr(pos);        // string — from pos to end
s.find("o");          // size_t — first index, or string::npos if missing
s.find("o", start);   // size_t — search starting at index start
s.rfind('o');         // size_t — last index
if (s.find("zz") == string::npos) {...}   // not found

s += 'a';  s += "bc";  s.push_back('d');  s.pop_back();   // append / remove last
s.append("!!");           // string& — same as s += "!!"
s.insert(pos, "XY");      // string& — inserts BEFORE index pos
s.erase(pos, len);        // string& — removes len chars starting at pos
s.replace(pos, len, "J"); // string& — swaps len chars at pos for "J"
s.resize(n, 'z');         // void — grow (padding with 'z') or truncate to n
s.clear();                // void
s.find_first_of("aeiou"); // size_t — first index of ANY of those chars (npos if none)
s.c_str();                // const char* — only for C APIs (printf, atoi)
s == t;  s < t;           // bool — direct compare, lexicographic (no strcmp needed)
reverse(s.begin(), s.end());  sort(s.begin(), s.end());   // in place

int d = c - '0';       // '7' -> 7
int k = c - 'a';       // 'c' -> 2 (index for int freq[26])
char ch = 'a' + k;     // 2 -> 'c'
stoi("42");            // int     stoll(...) for long long
to_string(5);          // string "5"
isdigit(c); isalpha(c); isalnum(c);   // int, nonzero = true
tolower(c); toupper(c);               // int — cast: (char)tolower(c)

for (char c : s) {...}                            // each char
for (int i = 0; i < (int)s.size(); i++) s[i];    // by index
stringstream ss(line);  string w;  while (ss >> w) {...}   // split on spaces
```
- `substr`, `+`, and `find` are `O(n)` — don't call `substr` in a hot loop.
- **Gotcha:** `find` returns `string::npos` (a huge unsigned number), **not -1** — always compare to `npos`. `s + 'a'` makes a new copy; `s += 'a'` appends in place (`O(1)`).

### `deque<T>` — double-ended vector
**Use when:** you push/pop at **both ends** (sliding window, BFS-ish queues).
```cpp
deque<int> d;   d.push_front(x); d.push_back(y);
d.front();      // int& — first
d.back();       // int& — last
d[i];           // int& — random access ok
d.pop_front();  d.pop_back();    // void — read front()/back() first
d.size();       // size_t — # of elements
d.empty();      // bool
d.clear();      // void
d.emplace_front(x);  d.emplace_back(x);   // build in place
d.insert(d.begin()+i, x);  d.erase(d.begin()+i);   // works, but O(n) — prefer the ends
```
- Both ends `O(1)`, random access `O(1)` but slower constant than vector.
- **Gotcha:** no contiguous memory — don't treat `&d[0]` like a C array.

### `list<T>` — doubly linked list
**Use when:** tons of insert/erase in the **middle** and you hold iterators to spots.
```cpp
list<int> l;  l.push_back(x);  auto it = l.begin();  l.erase(it);
l.front();  l.back();   // int& — ends only, no l[i]
l.size();   // size_t — # of elements
l.empty();  // bool
l.push_front(x);  l.pop_front();  l.pop_back();   // void
l.insert(it, x);   // iterator to the new element; O(1) at a known spot
l.erase(it);       // iterator to the NEXT element
l.remove(val);     // void — erases ALL elements equal to val
l.sort();  l.reverse();   // void — member versions (std::sort won't work: no random access)
l.splice(it, other);      // void — moves all of `other` in at it, O(1)
```
- Insert/erase at a known iterator `O(1)`; **no random access**.
- **Gotcha:** rarely the answer on OAs. Usually `vector` or `deque` wins on cache behavior. Reach for it only when the problem screams "splice/erase mid-list repeatedly."

### `array<T, N>` — fixed-size stack array
**Use when:** compile-time fixed size, want STL interface.
```cpp
array<int, 5> a = {1,2,3,4,5};
a[i];  a.at(i);  a.front();  a.back();   // int&
a.size();    // size_t — always N (5 here), fixed at compile time
a.empty();   // bool — false unless N == 0
```

---

## Container Adapters

### `stack<T>` — LIFO
**Use when:** matching/nesting (parens, monotonic stack, DFS iterative, undo).
```cpp
stack<int> s;  s.push(x);
s.top();       // int& — last pushed (UB if empty)
s.pop();       // void — removes top, doesn't return it
s.size();      // size_t — # of elements
s.empty();     // bool — ALWAYS check before top()/pop()
s.emplace(x);  // push, building in place
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
q.size();      // size_t — # of elements (BFS: level size = q.size())
q.empty();     // bool — ALWAYS check before front()/pop()
q.emplace(x);  // push, building in place
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
pq.size();     // size_t — # of elements (top-K: pop while pq.size() > k)
pq.empty();    // bool — ALWAYS check before top()/pop()
pq.emplace(d, node);   // push a pair without writing {d, node}
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
m.erase(k);          // size_t — # removed (0 or 1)
m.erase(it);         // iterator to the NEXT entry — use when erasing in a loop
m.size();            // size_t — # of keys
m.empty();           // bool
m.clear();           // void
m.insert({k, v});    // pair<iterator,bool> — .second == false if k already existed (NO overwrite)
m.emplace(k, v);     // same, built in place
m.contains(k);       // bool (C++20)
m.lower_bound(k);    // iterator to first key >= k   (m.end() if none)
m.upper_bound(k);    // iterator to first key >  k
for (auto& [k, v] : m) {...}     // sorted key order; v writable, k const

set<int> st;  st.insert(x);
st.count(x);     // 0 or 1
st.find(x);      // iterator, st.end() if missing
*st.begin();     // smallest
*st.rbegin();    // largest
st.insert(x);    // pair<iterator,bool> — .second == false if x was already there
st.erase(x);     // size_t — # removed (0 or 1)
st.erase(it);    // iterator to the NEXT element
st.size();       // size_t — # of DISTINCT elements
st.empty();      // bool
st.clear();      // void
st.contains(x);  // bool (C++20)
auto it = st.lower_bound(x);   // iterator to first >= x (st.end() if none)
auto it = st.upper_bound(x);   // iterator to first >  x
if (it != st.begin()) *prev(it);   // largest <= x (after upper_bound)
```
- All ops `O(log n)`. Iteration is in sorted order.
- **Gotcha:** `st.erase(x)` on a **multiset** removes **every** copy of `x` — use `st.erase(st.find(x))` to drop just one. `ms.count(x)` on a multiset is `O(log n + count)`; `equal_range(x)` gives the `[first, last)` pair of that key's run.
- **Gotcha:** `insert` on an existing key **does nothing** (no overwrite) — assign with `m[k] = v` when you mean to replace.
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
cnt.erase(k);    // size_t — # removed (0 or 1)
cnt.erase(it);   // iterator to the NEXT entry
cnt.size();      // size_t — # of distinct keys
cnt.empty();     // bool
cnt.clear();     // void
cnt.insert({k, v});   // pair<iterator,bool> — .second == false if k existed (NO overwrite)
cnt.emplace(k, v);    // same, built in place
cnt.contains(k);      // bool (C++20)
cnt.reserve(n);       // void — pre-size the table when n is known (fewer rehashes)
for (auto& [k, v] : cnt) {...}   // random order

unordered_set<int> seen;  seen.insert(x);
seen.count(x);   // 0 or 1
seen.find(x);    // iterator, seen.end() if missing
seen.erase(x);   // size_t — # removed (0 or 1)
seen.erase(it);  // iterator to the NEXT element
seen.size();     // size_t — # of distinct elements
seen.empty();    // bool
seen.clear();    // void
seen.contains(x);// bool (C++20)
seen.reserve(n); // void — pre-size the table
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
