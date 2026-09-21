# C++ OA Boilerplate & Fast I/O

Copy-paste (or retype) the top block to start every problem. Below it, the read patterns and a tiny test harness.

---

## The starter (paste this first, every time)
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---- your code ----

    return 0;
}
```
- `<bits/stdc++.h>` pulls in the whole standard library (GCC — works on HackerRank).
- The two `cin` lines unhook C++ streams from C stdio and stop flushing on every read → big speedup on large inputs. Only add them when you're not mixing `cin` with `scanf`.

---

## Common read patterns
```cpp
// Single values
int n; cin >> n;

// N integers into a vector
int n; cin >> n;
vector<int> v(n);
for (auto& x : v) cin >> x;             // note the & — reads in place

// Read until EOF
int x;
while (cin >> x) { /* ... */ }

// A whole line (careful after >>: consume the leftover newline first)
int n; cin >> n; cin.ignore();
string line; getline(cin, line);

// A grid of chars
int r, c; cin >> r >> c;
vector<string> g(r);
for (auto& row : g) cin >> row;

// A grid of ints
vector<vector<int>> a(r, vector<int>(c));
for (auto& row : a) for (auto& x : row) cin >> x;
```
- **Gotcha:** mixing `cin >> n` then `getline` — the `>>` leaves the `\n` in the buffer, so the first `getline` reads empty. Call `cin.ignore()` between them.

---

## Output
```cpp
cout << ans << "\n";                    // prefer "\n" over endl (endl flushes)
for (int x : v) cout << x << " ";
cout << "\n";
```
- Avoid `endl` in loops — it flushes every time and kills performance. Use `"\n"`.

---

## Tiny test harness (throw your own edge cases at it)
Keep a `tests.txt` next to your solution:
```
# run: ./sol < tests.txt
```
Edge cases to always try:
- **Empty / n = 0** input
- **Single element**
- **All equal** elements (ties)
- **Max size** input (the performance gate — generate a big one)
- **Negative numbers / overflow** (sums that exceed int → use `long long`)
- For queries: an operation on something absent (cancel an order that isn't there, pop empty)

Quick big-input generator (Python, for stress testing locally):
```python
import random
n = 200000
print(n)
print(' '.join(str(random.randint(-10**9, 10**9)) for _ in range(n)))
```
