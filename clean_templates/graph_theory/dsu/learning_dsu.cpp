#include <bits/stdc++.h>
using namespace std;

bool multicases_ = true;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                              tree_order_statistics_node_update>;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;

void pre_compute() {}

// DSU is an online query structure: the result of a current query can
// affect future queries. It works by connecting components using each
// component's root. Two standard optimizations are implemented below:
// 1) Union by Size, 2) Path Compression. Full explanation at the bottom
// of this file.
struct DSU {
  int cnt;
  vector<int> parent, sizes;
  void init(int n) {
    cnt = n;  // initially every node is its own component -> n components
    parent.resize(n + 1);
    sizes.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      parent[i] = i;
      sizes[i] = 1;
    }
  }

  int find_root(int u) {
    if (parent[u] == u) return u;
    return parent[u] = find_root(parent[u]);
  }

  int merge(int u, int v) {
    int root_u = find_root(u);
    int root_v = find_root(v);

    if (root_u == root_v) return 0;

    if (sizes[root_u] > sizes[root_v]) swap(root_u, root_v);

    parent[root_u] = root_v;
    sizes[root_v] += sizes[root_u];

    --cnt;  // merging 2 components into 1 decreases the component count
    return 1;
  }
};

// Example usage:
void solve(int tc) {
  int n, q;
  cin >> n >> q;
  // n elements from 1 to n (or use a map instead of a vector in DSU if
  // the elements aren't a dense 1..n range), then q queries.

  DSU d;
  d.init(n + 3);
  // +3 headroom is useful if you need to check indices just before/after
  // the valid range (and also covers 1-indexing).

  int qq, u, v;  // query type, first node, second node
  while (q--) {
    cin >> qq >> u >> v;
    if (qq == 1)
      d.merge(u, v);
    else if (qq == 2)
      cout << (d.find_root(u) == d.find_root(v) ? "YES" : "NO") << '\n';
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  pre_compute();

  int tc = 1;
  if (multicases_) cin >> tc;
  int total_tcs = tc;
  while (tc--) {
    solve(total_tcs - tc);
  }
  return 0;
}

/*
DSU (Disjoint Set Union)

DSU maintains multiple disjoint components while processing online
queries, meaning the result of a current operation can affect future
operations. Every component has a representative (root), and each node
eventually points toward the root of its component.

1) Union by Size
When merging two components, always attach the smaller tree to the
larger tree.

Why does this give O(log n) height?
Initially every node is its own tree of size 1: {1} {2} {3} {4}
Merge 1,2 -> {1,2} size 2. Merge 3,4 -> {3,4} size 2.
Merge the two components -> {1,2,3,4} size 4.
Whenever a node's depth increases, its component just got merged into a
component of at least the same size, so that component's size at least
doubles. So a node's depth can increase at most log2(n) times -- union
by size guarantees O(log n) tree height.

2) Path Compression
When calling find(x), traverse from x toward the root. After finding the
root, make every node on that path point directly to the root.
Before: 1 -> 2 -> 3 -> 4
After find(1): 1 -> 4, 2 -> 4, 3 -> 4
This makes future find() calls much faster.

Union by size + path compression together give an amortized complexity
of O(alpha(n)) per operation, where alpha(n) is the inverse Ackermann
function -- practically constant for any realistic n.
*/
