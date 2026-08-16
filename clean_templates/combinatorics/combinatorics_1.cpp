/*
Combinatorics notes / reference (no runnable code in this file).

--- Counting pairs (x, y) with max(x, y) = n ---
All pairs: (0,n)...(n,n) and (n,0)...(n,n), with (n,n) counted twice.
Total = (n+1)*2 - 1 = 2n + 1.

--- Grouping / "block" trick ---
5 seats, people a b c d e. Condition: a and b must sit beside each other.
Treat (a,b) as a single block -> 4 blocks total (the pair + 3 others).
The pair can be internally ordered in 2! ways (a,b or b,a).
Answer = 4! * 2!.

To count arrangements where a,b must NOT sit together:
total arrangements - arrangements where they sit together.

--- Circular arrangements: n!/n = (n-1)! ---
(a b c d) is the same arrangement as (b c d a) rotated by one seat, so
labeling seats overcounts every circular arrangement n times (one per
rotation). Dividing n! by n removes the duplicates, giving (n-1)!.
Equivalently: fix one person's seat, then arrange the rest -> (n-1)!.

Proof sketch:
Let S = set of all labeled-seat arrangements, |S| = n!.
Define x ~ y if x is a rotation of y. Each equivalence class has exactly
n elements (all rotations of a given circular arrangement are distinct
since people are distinct). So the number of circular arrangements is
|S| / n = n! / n = (n-1)!.

--- Addition rule (sum rule) ---
If a task is done by choosing exactly ONE of several mutually exclusive
options, total ways = sum of ways per option.
Example: 5 red balls OR 3 blue balls -> 5 + 3 = 8 choices.

--- Multiplication rule (product rule) ---
If a task consists of independent consecutive steps, total ways = product
of choices per step.
Example: password of 3 uppercase letters (26 each) + 2 digits (10 each)
-> 26 * 26 * 26 * 10 * 10.

--- Permutations (nPr) ---
Choose AND arrange r objects out of n distinct objects; order matters.
nPr = n! / (n-r)!
Derivation: position 1 has n choices, position 2 has n-1, ..., position r
has n-r+1 choices -> n*(n-1)*...*(n-r+1) = n!/(n-r)!.
Example: arrange 3 students out of 5 -> 5P3 = 5*4*3 = 60.

--- Combinations (nCr) ---
Choose r objects out of n distinct objects; order does NOT matter.
nCr = n! / (r! * (n-r)!)
Derivation: nPr counts every group of r objects r! times (once per
ordering of that group), so divide nPr by r!.
Example: committee of 3 from 5 students -> 5C3 = 10. {A,B,C}, {B,A,C},
and {C,B,A} are the same committee, counted once.
*/
