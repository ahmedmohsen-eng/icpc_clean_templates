#include <bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;  // don't forget to set this per problem

// Binary exponentiation: computes (n^m) % mod in O(log m).
// Usage: cout << fastpow(n, m);  the returned value is already reduced mod.
int fastpow(int n, int m) {
  if (m == 0) return 1;

  int ans = fastpow(n, m / 2) % mod;
  ans = (ans * ans) % mod;

  if (m & 1) ans = (ans * n) % mod;

  return ans;
}
