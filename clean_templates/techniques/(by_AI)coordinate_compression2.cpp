#include <bits/stdc++.h>
using namespace std;

// Works for either 1-indexed or 0-indexed input, depending on how the
// vector you pass in is laid out (see usage below).
void coord_comp_not_best(vector<int>& v) {  // must be passed by reference
  vector<int> sorted(v.begin(), v.end());   // same as: vector<int> sorted = v;
  sort(sorted.begin(), sorted.end());
  unordered_map<int, int> pos;

  // Starts at i=1 here because the vector passed in is expected to be
  // 1-indexed (size n+1, with index 0 unused).
  for (int i = 1; i < sorted.size(); i++) pos[sorted[i]] = i;

  for (auto& x : v) x = pos[x];
}

// Example usage:
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vector<int> v(n + 1);  // size n+1 so indices start at 1
  for (int i = 1; i <= n; i++) cin >> v[i];
  coord_comp_not_best(v);

  // Output also starts at index 1, matching the function's 1-indexed
  // convention (edit both sides together if you want 0-indexed instead).
  for (int i = 1; i <= n; i++) cout << v[i] << ' ';
}
