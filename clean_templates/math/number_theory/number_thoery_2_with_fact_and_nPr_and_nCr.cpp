#include <bits/stdc++.h>
using namespace std;

#define int long long

// Why is (a-b) always divisible by gcd(a,b)?
// Let g = gcd(a,b). Then a/g and b/g are integers, so a/g - b/g is also an
// integer, meaning (a-b)/g is an integer -- i.e. g divides (a-b).
// So gcd(a,b) = gcd(a, a-b) = gcd(b, a-b), i.e. gcd(a,b) = gcd(b, a-b).
// Instead of repeated subtraction, using modulus jumps straight there.

int gcd(int a, int b) {
  // gcd is always non-negative by definition (e.g. gcd(-1,0) = 1, not -1),
  // so take abs() at the base case.
  if (b == 0) return abs(a);
  return gcd(b, a % b);

  // This works even when a < b: e.g. a=3, b=9 -> next call is
  // gcd(9, 3%9=3), so they effectively swap in one step.
  // Complexity: O(log(min(a,b))). Swapping happens at most about once
  // every two steps when needed, so it doesn't change the asymptotic
  // complexity -- still O(log n) overall.
}

// Euclidean algorithm rests on three facts:
// 1) gcd(a,b) = gcd(b,a)
// 2) gcd(a,0) = |a|
// 3) gcd(a,b) = gcd(b, a%b)

// --- LCM ---
// After factorizing a and b, a number divisible by both must contain, for
// every prime, at least the larger of the two exponents.
// Example: 6 = 2^1*3^1, 8 = 2^3 -> lcm needs 2^3 * 3^1 = 24.
//
// Shortcut: lcm(a,b) = a*b / gcd(a,b). Why does this work? Multiplying a
// and b together duplicates every shared (common) prime factor twice;
// dividing by gcd(a,b) removes exactly one of those duplicate copies,
// leaving each prime at its max needed exponent.
int lcm(int x, int y) {
  // If either is 0, the answer is 0 (and naively dividing by gcd(x,y)
  // would divide by zero in that case, so handle it explicitly).
  if (x == 0 || y == 0) return 0;

  // Divide by gcd first, then multiply -- doing x*y first risks overflow
  // even though the final answer would have fit.
  return abs(x / gcd(x, y) * y);
}

// gcd takes, for each prime, the SMALLER of the two exponents; lcm takes
// the LARGER. Together: gcd(a,b) * lcm(a,b) = |a*b|.
// Also: lcm(a,b) % gcd(a,b) == 0.

// Can fastpow be optimized with DP/memoization? No -- there are no
// overlapping subproblems (each call has a distinct argument), unlike
// e.g. fib(n) = fib(n-1) + fib(n-2) where fib(3) gets computed multiple
// times independently. fastpow's call tree (fastpow(13) -> fastpow(6) ->
// fastpow(3) -> ...) never revisits the same argument.

// --- Modular arithmetic helpers (avoid intermediate overflow) ---
// A common contest modulus: int mod = 1'000'000'007;  (check whether it's
// already defined before redeclaring it).

int mod_add(int a, int b, int mod = 1'000'000'007) {
  return ((a % mod + mod) + (b % mod + mod)) % mod;
}
int mod_sub(int a, int b, int mod = 1'000'000'007) {
  return (((a % mod + mod) - (b % mod + mod)) + mod) % mod;
}
int mod_mul(int a, int b, int mod = 1'000'000'007) {
  // Cast to __int128 before multiplying (not after), otherwise the
  // multiplication itself can overflow before the cast ever applies.
  __int128 ans = (__int128)(a % mod + mod) * (b % mod + mod) % mod;
  return ans;  // fits back in the function's return type after % mod
}

// --- Fast (binary) exponentiation ---
// Naive pow(x,y) multiplies x by itself y times; this does it in O(log y)
// by squaring. Don't approximate MOD with a float literal like 1e9 --
// use an exact integer literal to avoid precision loss.
// Uses MOD (not mod) as the parameter name here to avoid shadowing/
// confusion with any global `mod` variable.
// Assumes y >= 0.
int fastpow(int x, int y, int MOD = 1000'000'007) {
  if (y == 0) return 1;

  x %= MOD;

  // Halve y, square the result, and if y is odd, multiply in one more
  // factor of x to make up for the floor-division rounding down.
  int ret = fastpow(x, y / 2, MOD);
  ret = mod_mul(ret, ret, MOD);
  if (y % 2 == 1) ret = mod_mul(ret, x, MOD);

  return ret;
}

// Iterative version of the same idea.
int fastpow_iterative(int a, int b, int MOD = 1000'000'007) {
  a %= MOD;

  int ret = 1;
  while (b > 0) {
    if (b & 1) {  // b&1 == b%2==1: checks the lowest bit
      ret = mod_mul(ret, a, MOD);
    }
    a = mod_mul(a, a, MOD);
    b >>= 1;  // same as b /= 2
  }
  return ret;
}

// --- Modular inverse ---
// x is the modular inverse of y under mod m if (x*y) % m == 1.
// A number has a modular inverse mod m only if it's coprime with m.
//
// Fermat's little theorem gives the inverse directly, but only when MOD_
// is prime (and NUM_, MOD_ are coprime).
int fermat_little_mod_inverse(int NUM_, int MOD_) {
  return fastpow(NUM_, MOD_ - 2, MOD_);
}

// Single entry point for "which mod-inverse method to use" -- swap the
// body here to change the implementation everywhere else calls this.
int mod_inverse(int x, int y) { return fermat_little_mod_inverse(x, y); }

// --- Precomputed factorials + inverse factorials (for nPr / nCr) ---
const int N = 1'000'000;
int fact[N + 1], inv_fact[N + 1];

// Builds fact[] and inv_fact[] up to N. Safe as long as mod is prime and
// N < mod.
void build_fact_and_fact_inv(int mod = 1'000'000'007) {
  fact[0] = fact[1] = 1;
  inv_fact[0] = inv_fact[1] = 1;  // mod_inverse(1, mod) == 1

  for (int i = 2; i <= N; i++) {
    fact[i] = mod_mul(fact[i - 1], i, mod);
    inv_fact[i] = mod_inverse(fact[i], mod);
  }
}

/*
Faster alternative: builds fact[]/inv_fact[] in O(N) instead of O(N log N),
by computing only ONE modular inverse (at index N) instead of one per
index (the version above calls fastpow inside mod_inverse every iteration).

Identity used: since fact[i] = fact[i-1] * i, dividing both sides by i
gives fact[i-1] = fact[i] / i, so in modular terms:
inv_fact[i-1] = inv_fact[i] * i

void build_fact_and_fact_inv(int mod = 1'000'000'007) {
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = mod_mul(fact[i-1], i, mod);
  }

  inv_fact[N] = mod_inverse(fact[N], mod);  // only inverse computed
  for (int i = N; i >= 1; i--) {
    inv_fact[i-1] = mod_mul(inv_fact[i], i, mod);
  }
}
*/

// Counting basics: nPr = n! / (n-r)!,  nCr = n! / ((n-r)! * r!)
// Call build_fact_and_fact_inv() once before using nPr/nCr below.
// Important: must have 0 <= r <= n, otherwise inv_fact[n-r] is an
// out-of-bounds access.
int nPr(int n, int r, int mod = 1'000'000'007) {
  if (r < 0 || r > n) return 0;  // matches convention used by many libraries
  return mod_mul(fact[n], inv_fact[n - r], mod);
}

int nCr(int n, int r, int mod = 1'000'000'007) {
  if (r < 0 || r > n) return 0;
  int ans = fact[n];
  ans = mod_mul(ans, inv_fact[r], mod);      // divide by r! (mod-safe)
  ans = mod_mul(ans, inv_fact[n - r], mod);  // divide by (n-r)! (mod-safe)
  return ans;
}

bool multi_cases = false;
void solve() {}

signed main() {
  int ttt = 1;
  if (multi_cases) cin >> ttt;
  while (ttt--) {
    solve();
  }
}

// ---- Notes / fixes / things to remember ----
// - fastpow: check `y == 0` as the base case, not `y == 1`.
// - fastpow: reduce x mod MOD at the very start, before recursing.
// - fastpow: when y is odd, multiply the extra factor by x, not by y.
// - mod_mul: cast to __int128 BEFORE multiplying, or the multiplication
//   itself overflows before the wider type takes effect.
// - nPr/nCr: always validate 0 <= r <= n first, or inv_fact[n-r] can read
//   out of bounds.
// - Don't forget to call build_fact_and_fact_inv() before using nPr/nCr.
