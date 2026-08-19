// Instead of using the call stack to recurse, simulate it (same logic)
// with an explicit stack storing the nodes to process.

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj(n);
vector<bool> vis(n, false);

void DFS(int start) {
  stack<int> st;
  st.push(start);

  vis[start]=true; // mark visited, then push its unvisited children
  
  while (!st.empty()) {
    int u = st.top();
    st.pop();

    if (vis[u]) continue;
  
    for (int v : adj[u]) {
      if (!vis[v]) st.push(v),vis[v]=true;
    }

    // To match the same visiting order as the recursive version, push
    // children in reverse (stack is LIFO, so reversing restores order):
    // for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it)
    //   st.push(*it);
  }
}

// ---- Notes / fixes / things to remember ----
// - Watch variable naming for the stack (e.g. `st` vs `s`) to avoid
//   confusing typos when copying this template into a solution.
