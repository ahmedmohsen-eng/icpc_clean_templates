#include <bits/stdc++.h>
using namespace std;

#define int long long

// a % b = a - floor(a/b)*b  (we keep subtracting b until the value is
// smaller than b).

// gcd(a,b) = gcd(b,a) = gcd(b%a, a).
// Proof sketch: let g = gcd(a,b). Then a/g and b/g are integers, so
// (a/g - b/g) is an integer, meaning (a-b) is also divisible by g.
// So replacing one operand with (that operand minus the other) doesn't
// change the gcd -- and repeating that subtraction is exactly what "%"
// computes. Hence gcd(a,b) = gcd(b%a, a).
// Base case: gcd(a,0) = a.

// Bezout's identity: ax + by = gcd(a,b) always has integer solutions
// x, y (proved constructively via the extended Euclidean algorithm).

signed main() {}
