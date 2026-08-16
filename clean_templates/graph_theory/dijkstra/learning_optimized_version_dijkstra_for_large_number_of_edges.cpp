// Optimization: only push to the priority queue when a strictly shorter
// path is found (dis[u] + cost < dis[v]), instead of using a vis[] array
// and checking it on pop.
//
// Old approach (vis[] check only):   O((E + V) log E), O(E) space.
// This approach (dis[] check):       O((E + V) log V), O(V) space (fewer
//                                     redundant entries in the queue).
//
// This shines most on dense graphs (large E), since it prevents flooding
// the priority queue with redundant path updates.

#include <bits/stdc++.h>
using namespace std;

bool multicases_ = false;

#define int long long

struct node {
  int idx, cost;
};

struct cmp {
  bool operator()(node& a, node& b) { return a.cost > b.cost; }
};

int N = 2e5 + 5;
vector<vector<node>> adj(N);
vector<int> parent(N, -1);
vector<int> dis(N, 1e18);

int n, m;

int dijkstra(int src, int target) {
  priority_queue<node, vector<node>, cmp> pq;

  dis[src] = 0;
  pq.push({src, 0});

  while (!pq.empty()) {
    node u = pq.top();
    pq.pop();

    if (u.cost > dis[u.idx]) continue;  // outdated entry, skip

    if (u.idx == target) return u.cost;

    for (auto& v : adj[u.idx]) {
      int newDist = u.cost + v.cost;
      if (newDist < dis[v.idx]) {
        dis[v.idx] = newDist;
        parent[v.idx] = u.idx;
        pq.push({v.idx, newDist});
      }
    }
  }

  return -1;
}

void graph_clear(int n) {
  for (int i = 1; i <= n; i++) {
    adj[i].clear();
    parent[i] = -1;
    dis[i] = 1e18;
  }
}

void solve(int tc) {
  int src, target;
  cin >> n >> m;
  src = 1, target = n;

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
