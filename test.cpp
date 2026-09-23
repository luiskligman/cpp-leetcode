#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> v;

  v.push_back(1);
  v.push_back(2);

  for (const auto& n : v) {
    cout << n;
  }
  cout << "\n";
  cout << v[0]; 

  return 0;
}