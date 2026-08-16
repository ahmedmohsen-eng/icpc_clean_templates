#include <bits/stdc++.h>
using namespace std;

bool multicases_ = false;

#define int long long

struct node {
  int idx, cost, par;
};

struct cmp {
  bool operator()(node& a, node& b) { return a.cost > b.cost; }
};

int N = 2e5 + 5;
vector<vector<node>> adj(N);
vector<bool> vis(N, false);
vector<int> parent(N, -1);
int n, m;

int dijkstra(int src, int target) {
  priority_queue<node, vector<node>, cmp> pq;

  pq.push({src, 0, -1});  // src's parent is -1

  while (!pq.empty()) {
    node u = pq.top();
    pq.pop();

    if (vis[u.idx]) continue;

    vis[u.idx] = true;
    // The popped node is optimal, so it's the correct parent for its
    // children. Assign parent[] before returning on target match below.
    parent[u.idx] = u.par;

    if (u.idx == target) return u.cost;

    for (auto& v : adj[u.idx]) {
      if (!vis[v.idx]) {
        pq.push({v.idx, u.cost + v.cost, u.idx});  // u.idx is v.idx's parent
      }
    }
  }

  return -1;
}

void graph_clear(int n) {
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    vis[i] = false;
    parent[i] = -1;
  }
}

void solve(int tc) {
  int src, target;
  cin >> n >> m;
  src = 1, target = n;  // or cin >> src >> target; depends on the problem

  graph_clear(n);

  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  int ans = dijkstra(src, target);

  if (ans == -1) {
    cout << -1 << '\n';
  } else {
    vector<int> path;
    int cur = target;
    while (cur != -1) {
      path.push_back(cur);
      cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    for (auto& step : path) cout << step << ' ';

    cout << '\n';
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int tc = 1;
  if (multicases_) cin >> tc;
  int total_tcs = tc;
  while (tc--) {
    solve(total_tcs - tc);
  }
  return 0;
}

// ---- Notes / fixes / things to remember ----
// - Assign parent[u.idx] BEFORE the `if (u.idx == target) return ...`
//   check, not after -- returning early skips the assignment for the
//   target node otherwise.
