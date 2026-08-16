#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj(n);
vector<bool> vis(n, false);

// Preferred version: check vis[v] before recursing (avoids useless calls).
void DFS(int u) {
  vis[u] = true;
  for (auto v : adj[u]) {
    if (!vis[v]) {  // acts as the base case
      DFS(v);
    }
  }
}

// Alternative version (works, but recurses into already-visited nodes
// before checking, which wastes calls -- prefer the version above):
/*
void DFS(int u) {
  if (vis[u]) return;
  vis[u] = true;
  for (auto v : adj[u]) {
    DFS(v);
  }
}
*/
