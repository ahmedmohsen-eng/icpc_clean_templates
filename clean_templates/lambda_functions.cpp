#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  // & in the parameter (int& x) captures the variable itself (reference), not
  // a copy. This is different from & inside the capture list [].
  // [] captures nothing from the enclosing scope. [&] captures all
  // surrounding variables by reference (can read/modify them).
  auto inc = [](int& x) {
    x++;
    return x;
  };
}

// ---- Notes / fixes / things to remember ----
// - Lambdas need a trailing ';' after the closing '}' when defined as a
//   statement (e.g. `auto inc = [](...) {...};`), unlike normal functions.
