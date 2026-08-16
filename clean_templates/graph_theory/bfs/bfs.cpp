#include <bits/stdc++.h>
using namespace std;

struct node {
  int index, cost;
};

int n, m;
vector<vector<int>> adj;
// Directed graph with weights: use vector<vector<node>> adj instead.

vector<bool> vis;

void bfs(int src) {
  vis.assign(n + 1, false);

  queue<int> q;

  vis[src] = true;
  q.push(src);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& v : adj[u]) {
      if (!vis[v]) {
        q.push(v);
        vis[v] = true;
      }
    }
  }
}

// Shortest path (unweighted graph) via BFS levels.
// After calling bfs_shortest_path(start), lvls[end] gives the distance.
// Works start->end or end->start (BFS from either endpoint).
vector<int> lvls;

void bfs_shortest_path(int src) {
  lvls.assign(n + 1, -1);

  queue<int> q;

  lvls[src] = 0;
  q.push(src);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& v : adj[u]) {
      if (lvls[v] == -1) {
        lvls[v] = lvls[u] + 1;
        q.push(v);
      }
    }
  }
}

// If the target may be unreachable, check dist[target] == -1 before using
// it (e.g. before reconstructing a path), and return early / handle it.

// bfs_shortest_path + reconstructing the actual path via parent pointers.
vector<int> parent;
void bfs_build_shortest_path(int src) {
  lvls.assign(n + 1, -1);
  parent.assign(n + 1, -1);

  queue<int> q;

  vis[src] = true;
  q.push(src);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& v : adj[u]) {
      if (lvls[v] == -1) {
        lvls[v] = lvls[u] + 1;
        parent[v] = u;
        q.push(v);
      }
    }
  }
}

// Call bfs_build_shortest_path() first, then this to extract the path.
vector<int> path;
void bfs_get_shortest_path(int target) {
  path.clear();

  if (lvls[target] == -1) return;  // unreachable

  int cur = target;
  while (cur != -1) {
    path.push_back(cur);
    cur = parent[cur];
  }
  reverse(path.begin(), path.end());
}

// Multi-source BFS: don't forget to pass the sources vector.
void multi_source_bfs(vector<int>& sources, int src) {
  lvls.assign(n + 1, -1);

  queue<int> q;

  for (int src : sources) {
    lvls[src] = 0;
    q.push(src);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto& v : adj[u]) {
      if (lvls[v] == -1) {
        lvls[v] = lvls[u] + 1;
        q.push(v);
      }
    }
  }
}

// Cycle detection, undirected graph (same idea as DFS undirected check).
// Careful with terminology: undirected, not "indirected".
bool has_cycle_undirected_bfs() {
  vis.assign(n + 1, {});

  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;

    queue<pair<int, int>> q;  // {child, parent}

    q.push({i, -1});
    vis[i] = true;

    while (!q.empty()) {
      auto [u, parent] = q.front();
      q.pop();

      for (auto& v : adj[u]) {
        if (!vis[v]) {
          vis[v] = true;
          q.push({v, u});
        } else if (v != parent) {
          return true;
        }
      }
    }
  }

  return false;
}

// Cycle detection, directed graph, via indegrees (Kahn's algorithm).
// (The DFS version instead uses a 3-color visited array.)
// This is also the basis of BFS topological sort below.
bool has_cycle_directed_bfs() {
  vector<int> indegree(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    for (auto& v : adj[i]) {
      indegree[v]++;
    }
  }

  queue<int> q;

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  int processed = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    processed++;

    for (auto& v : adj[u]) {
      indegree[v]--;

      if (indegree[v] == 0) {
        q.push(v);
      }
    }
  }

  return processed != n;
}

// Kahn's algorithm topological sort. Not void -- returns the topo order.
// If the graph has a cycle, returns {} (empty vector).
// Check per-problem whether the result needs to be reversed.
vector<int> topo_sort_bfs() {
  vector<int> indegree(n + 1, 0);
  vector<int> topo;

  for (int i = 1; i <= n; i++) {
    for (auto& v : adj[i]) {
      indegree[v]++;
    }
  }

  queue<int> q;

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    topo.push_back(u);

    for (auto& v : adj[u]) {
      indegree[v]--;

      if (indegree[v] == 0) {
        q.push(v);
      }
    }
  }

  if ((int)topo.size() != n) return {};  // cycle detected

  return topo;
}

bool is_bipartite() {
  vector<int> color(n + 1, -1);

  for (int i = 1; i <= n; i++) {
    if (color[i] != -1) continue;

    queue<int> q;

    color[i] = 0;
    q.push(i);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto& v : adj[u]) {
        if (color[v] == -1) {
          color[v] = 2 - color[u];  // or: color[v] = color[u] ^ 1;
          q.push(v);
        } else if (color[v] == color[u]) {
          return false;
        }
      }
    }
  }
  return true;
}

// A graph is a tree iff: it has n-1 edges AND is connected (undirected).
// For a directed graph: connected + no cycle.

signed main() { return 0; }

// ---- Notes / fixes / things to remember ----
// - vis[v] must be marked true at push time (not pop time) in BFS, or nodes
//   can be enqueued multiple times before being visited.
// - When reconstructing the path from parent[], watch the loop variable
//   naming so it doesn't shadow the global `parent` array.
// - When computing indegrees, iterate adjacency lists with a name that
//   doesn't collide with other loop variables in the same scope.
