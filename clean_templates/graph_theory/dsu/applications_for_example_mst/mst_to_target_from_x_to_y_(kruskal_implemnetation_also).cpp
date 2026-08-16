// Goal: find the path (and its cost) between two specific nodes "from"
// and "dest" inside the MST, not just build the MST.
//
// Approach: first build the full MST via Kruskal. Since the MST is a
// tree, root it at "from" and store each vertex's parent + the edge cost
// via a DFS. Then follow parent pointers from "dest" back to "from" and
// reverse the result to get the path from "from" to "dest".

#include <bits/stdc++.h>
using namespace std;

bool multicases_ = false;

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
#define int long long

void pre_compute() {}

struct DSU {
  int cnt;
  vector<int> parent, sizes;
  void init(int n) {
    cnt = n;
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

    --cnt;
    return 1;
  }
};

// #define int long long above keeps summed costs safe from overflow.
// "edge" holds {u, v, cost} (used while reading input / building MST);
// "to" holds just {v, cost} (used in the adjacency list, since the
// source node is already implied by the vector index).
struct edge {
  int u, v, cost;
};

struct to {
  int v, c;
};

struct cmp {
  bool operator()(edge& a, edge& b) {
    return a.cost > b.cost;  // min-heap: smallest cost first
  }
};

void solve(int tc) {
  int n, m;
  cin >> n >> m;

  priority_queue<edge, vector<edge>, cmp> pq;

  edge tmp;

  while (m--) {
    cin >> tmp.u >> tmp.v >> tmp.cost;
    pq.push(tmp);
  }

  DSU d;
  d.init(n);

  int taken = 0;

  vector<to> parent(n + 3, {-1, 0});
  vector<vector<to>> adj(n + 3);

  while (!pq.empty() && taken != n - 1) {
    auto [u, v, c] = pq.top();
    pq.pop();

    if (d.merge(u, v)) {
      taken++;
      adj[u].push_back({v, c});
      adj[v].push_back({u, c});
    }
  }

  if (taken != n - 1) {
    // no MST
    return void(cout << "IMPOSSIBLE\n");
  }

  // Because the MST is a tree, a single DFS from any root reaches every
  // node exactly once -- no visited array needed.
  function<void(int, int)> dfs = [&](int u, int p) {
    for (auto& [v, c] : adj[u]) {
      if (v == p) continue;
      parent[v] = {u, c};
      dfs(v, u);
    }
  };

  int from;
  cin >> from;  // root of the tree for this query

  dfs(from, -1);

  int dest;
  cin >> dest;  // path target

  // In a tree, any node can be the root, so "from" doesn't need to be
  // fixed globally.
  int total_cost = 0;

  vector<edge> ans;

  while (parent[dest].v != -1) {
    ans.push_back({parent[dest].v, dest, parent[dest].c});
    dest = parent[dest].v;
  }
  reverse(ans.begin(), ans.end());

  for (auto& [u, v, c] : ans)
    cout << u << ' ' << v << " and cost is : " << c << '\n', total_cost += c;

  cout << "total cost is : " << total_cost << '\n';
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
Example input (last two numbers are "from" and "dest"):

4 6
1 2 3
1 3 2
2 3 3
2 3 2
3 4 4
2 4 3
1 4
*/
