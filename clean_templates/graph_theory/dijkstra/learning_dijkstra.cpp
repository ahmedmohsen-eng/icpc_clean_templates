// Conditions: all weights are non-negative (positive or zero).
// Works on directed or undirected graphs (for undirected, add edges both
// ways: adj[u] and adj[v]).
// Visualization: https://visualgo.net/en/sssp

#include <bits/stdc++.h>
using namespace std;

struct node {
  int idx, cost;
};

struct cmp {
  bool operator()(node& a, node& b) {
    return a.cost > b.cost;  // smaller cost comes first; ties don't matter
  }
};

int n, m;
vector<vector<node>> adj;
vector<bool> vis;

// Time complexity: O((V+E) log V).
// For a connected graph: O(E log V), since E >= V-1.

int dijkstra(int src, int target) {
  priority_queue<node, vector<node>, cmp> pq;

  pq.push({src, 0});  // priority always goes to the lowest-cost node

  while (!pq.empty()) {
    node u = pq.top();
    pq.pop();

    // Once popped, a node's distance is final (can't be beaten later)
    // because of how the priority queue orders entries.
    if (u.idx == target) {
      return u.cost;
    }

    if (vis[u.idx]) {  // check target before skipping visited nodes
      continue;
    }

    vis[u.idx] = true;
    for (auto& v : adj[u.idx]) {
      if (!vis[v.idx]) {
        // When a vertex is popped from the priority queue for the first
        // time, it has its minimum possible distance.
        pq.push({v.idx, u.cost + v.cost});
      }
    }
  }

  return -1;
}

signed main() { return 0; }

// ---- Notes / fixes / things to remember ----
// - Struct keyword is `struct`, not `strcut`.
// - The comparator struct needs a trailing ';' after its closing '}'.
// - Popped element type from the priority queue is `node`, not `int`.
// - Be consistent with member naming: this template uses `idx`, not
//   `index` -- mixing them up is a common copy-paste bug.
// - Use `src`, not `st`, when naming the starting node parameter.
