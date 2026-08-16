#include <bits/stdc++.h>
using namespace std;

// Careful with comparisons after this define, e.g. min(x, 0LL) not min(x, 0).
#define int long long

bool is_prime_or_no(int n) {
  if (n == 1 || n == 0) return false;
  bool ok = true;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ok = false;
      break;
    }
  }
  return ok;
}

// Basic (non-sieve) versions: prime_factors_basic gets the prime factors of
// a single n; no_divisors_basic counts its divisors.
vector<int> factors_basic;
void prime_factors_basic(int n) {
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      factors_basic.push_back(i);
      n /= i;
    }
  }
  if (n > 1) factors_basic.push_back(n);  // remaining factor, if prime
}

int no_divisors_basic(int n) {
  int cnt = 1;  // start at 1 to account for i=1, since the loop starts at 2
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      if (n == i * i)
        cnt++;
      else
        cnt += 2;
    }
  }
  return cnt;
}

// vector<bool> vs vector<char>:
// vector<bool> is a special container storing one bit per element (8x less
// memory than vector<char>'s one byte per element), but each access needs
// extra bit operations so it's a bit slower per-access. For large sieves
// the memory/cache savings usually outweigh that cost, but which is faster
// depends on the algorithm, compiler, and hardware.

// Sieve of Eratosthenes. Idea: mark 0 and 1 as not prime, then for every
// unmarked (still-prime) i, mark all its multiples as not prime. If a
// number was never marked by a smaller prime, it stays prime.
// Starts each inner loop at i*i instead of i*2, since every multiple of i
// below i*i has already been marked by a smaller prime factor.
vector<bool> sieve(int n) {
  vector<bool> isprime(n + 1, true);
  isprime[0] = isprime[1] = 0;
  for (int i = 2; i * i <= n; i++) {
    if (isprime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isprime[j] = false;
      }
    }
  }

  // Complexity: O(n log log n). Starting from i*i instead of i*2 only
  // improves the constant factor, not the asymptotic complexity -- the
  // sum n + n/2 + n/3 + ... over primes is the harmonic-like series that
  // gives log log n.

  return isprime;
}

// Sieve that also computes each number's smallest prime factor, so any
// number in [1, n] can be factorized afterward in O(log n).
// smallest_prime_factor[x] = 0 for x = 0 or 1.
vector<int> smallest_prime_factor;

void sieve_with_factorization(int n) {
  smallest_prime_factor.assign(n + 1, 0);

  vector<int> isprime(n + 1, true);
  isprime[0] = isprime[1] = 0;
  for (int i = 2; i <= n; i++) {
    if (isprime[i]) {
      smallest_prime_factor[i] = i;

      for (int j = i * i; j <= n; j += i) {
        isprime[j] = false;

        if (smallest_prime_factor[j] == 0)  // keep only the smallest
          smallest_prime_factor[j] = i;
      }
    }
  }
}

// Factorize x using smallest_prime_factor[] (must call
// sieve_with_factorization first). O(log x) per call.
vector<int> prime_factors_for(int x) {
  vector<int> prime_factors_local;

  int cur_prime_factor;
  while (x != 1) {
    cur_prime_factor = smallest_prime_factor[x];
    prime_factors_local.push_back(cur_prime_factor);
    x /= cur_prime_factor;
  }

  return prime_factors_local;
}

// Precompute the number of divisors for every number from 1 to n, by
// letting each i "vote" for all of its multiples.
// Complexity: O(n log n) -- the inner loop total work is the harmonic
// series n*(1 + 1/2 + 1/3 + ...) ~ n ln(n).
vector<int> divisors;
void cnt_divisors_1toN(int n) {
  divisors.assign(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      divisors[j]++;
    }
  }
}

// To count the divisors of one number via prime factorization: if
// n = p1^a1 * p2^a2 * ... , the divisor count is (a1+1)*(a2+1)*...
// Example: 24 = 2^3 * 3^1 -> (3+1)*(1+1) = 8 divisors: 1,2,3,4,6,8,12,24.
// Example: 6 = 2^1 * 3^1 -> (1+1)*(1+1) = 4 divisors: 1,2,3,6.

// Number theory facts worth remembering:
// - The minimum number of divisors for any n > 1 is 2, achieved exactly
//   when n is prime.
// - Every number's smallest divisor (other than 1) is a prime.
// - The only even prime is 2.
// - To factorize n, it's enough to check divisors up to sqrt(n); if none
//   are found, n is prime.
// - A number has an even number of divisors unless it's a perfect square,
//   in which case it has an odd number of divisors.
// - A number has exactly 3 divisors iff it's a prime squared: the
//   divisors are 1, sqrt(n), and n itself.
// - After dividing out all prime factors up to sqrt(n), if what remains
//   is > 1, that remainder must itself be prime -- otherwise it would
//   have a prime factor <= sqrt(remainder) <= sqrt(original n), which
//   would already have been divided out.
// - A composite number can't have two factors both greater than sqrt(n),
//   since their product would exceed n.

#define add_mod(a, b, m) (((a % m) + (b % m) + m) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)

// Naive mul_mod can overflow long long; this version widens to __int128
// for the multiplication, then narrows back after the modulus.
inline long long mul_mod(long long a, long long b, long long m) {
  a = (a % m + m) % m;  // (a + m) % m alone only works if a >= -m
  b = (b % m + m) % m;
  return (__int128)a * b % m;
}

constexpr double EPS = 1e-9;
constexpr int INF = 1 << 30, Mod = 1e9 + 7;
constexpr long long LINF = 1LL << 62;
const char* yes = "YES\n";
const char* no = "NO\n";

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x)
#endif

// Binary exponentiation: (n^m) % mod in O(log m). mod defaults to 1e9+7
// but can be overridden per call.
int fastpow(int n, int m, int mod = 1e9 + 7) {
  if (m == 0) return 1;

  int ans = fastpow(n, m / 2, mod) % mod;
  ans = (ans * ans) % mod;

  if (m & 1) ans = (ans * n) % mod;

  return ans;
}

/*
Index of what's in this file:

1. cnt_divisors_1toN(n) -- precompute divisor counts for 1..n, stored in
   the global `divisors` vector. O(n log n).

2. sieve_with_factorization(n) -- fills the global `smallest_prime_factor`
   vector (O(n log log n)); then prime_factors_for(x) factorizes any
   x <= n using it in O(log x).

3. sieve(n) -- returns a vector<bool> of primality for 0..n. O(n log log n).

4. fastpow(n, m, mod) -- modular binary exponentiation.

5. Basic (non-sieve) helpers: prime_factors_basic(n) (fills
   factors_basic), no_divisors_basic(n) (returns an int -- check whether
   `#define int long long` applies before relying on its range).
*/

bool multi_cases = false;

void solve(const int& t) {}

signed main() {
  cin.exceptions(cin.failbit);  // helps catch malformed input early

  ios::sync_with_stdio(0);
  cin.tie(0);
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif

  int test_cases = 1;
  if (multi_cases) cin >> test_cases;
  for (int i = 1; i <= test_cases; i++) {  // 1-indexed test cases
    solve(i);
  }

  return 0;
}

// ---- Notes / fixes / things to remember ----
// - Sieve loops must start at i*i, not i (off-by-logic bug: starting at i
//   re-marks numbers already covered by smaller primes, which still
//   works but wastes time -- the real bug to avoid is looping the OUTER
//   sieve condition as `i <= n` instead of `i*i <= n`).
// - In sieve_with_factorization, the inner loop must use `j += i`
//   (multiples of i), not `j++`.
// - smallest_prime_factor should be declared as vector<int>, and the
//   `isprime` helper inside sieve_with_factorization must be initialized
//   to `true`, not `false`.
// - prime_factors_for must return the local vector (prime_factors_local),
//   not the global one -- otherwise results leak/accumulate across calls.
// - "prime divisors" vs "prime factors": these template comments mean
//   the same thing; don't let the wording confuse you mid-contest.
// - Remember the +1 when sizing arrays/vectors to be inclusive of n.
// - If output is very large, the freopen("out.txt", ...) lines under
//   #ifndef ONLINE_JUDGE are for local testing only -- don't leave them
//   uncommented when submitting, or the judge run can behave unexpectedly.
// - Any expensive precomputation (sieve, factorial table, etc.) should
//   run once outside solve(), not once per test case.
