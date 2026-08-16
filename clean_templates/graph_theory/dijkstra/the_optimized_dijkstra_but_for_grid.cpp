#include <bits/stdc++.h>
using namespace std;

bool multicases_ = false;

struct point {
  int x, y;
};

struct node {
  int x, y;
  long long cost;
};

// 4-directional movement.
vector<int> dx = {-1, 1, 0, 0};
vector<int> dy = {0, 0, -1, 1};

// 8-directional movement (uncomment to allow diagonals):
// vector<int> dx = {-1, 1, 0, 0, -1, -1, 1, 1};
// vector<int> dy = {0, 0, -1, 1, -1, 1, -1, 1};
//
// If diagonal moves cost extra:
// const double diagonal_bonus = sqrt(2.0);  // ~1.41421356
// vector<int> diagonal_cost = {0, 0, 0, 0, diagonal_bonus, diagonal_bonus,
//                               diagonal_bonus, diagonal_bonus};

struct cmp {
  bool operator()(const node& a, const node& b) const {
    return a.cost > b.cost;
  }
};

vector<vector<int>> grid;
vector<vector<point>> parent;
vector<vector<long long>> dis;

int R, C;

// Helper to validate boundary limits.
bool isvalid(int row, int col) {
  return (row >= 1 && row <= R && col >= 1 && col <= C);
}

long long dijkstra(point src, point target) {
  priority_queue<node, vector<node>, cmp> pq;

  dis[src.x][src.y] = 0;
  pq.push({src.x, src.y, 0});

  while (!pq.empty()) {
    node u = pq.top();
    pq.pop();

    if (u.cost > dis[u.x][u.y]) continue;  // outdated entry, skip

    if (u.x == target.x && u.y == target.y) return u.cost;

    for (int i = 0; i < (int)dx.size(); i++) {
      int nx = u.x + dx[i];
      int ny = u.y + dy[i];

      if (isvalid(nx, ny)) {
        long long edgeCost = grid[nx][ny];
        long long newDist = u.cost + edgeCost;

        // With diagonal cost enabled instead use:
        // long long edgeCost = grid[nx][ny] + diagonal_cost[i];

        if (newDist < dis[nx][ny]) {
          dis[nx][ny] = newDist;
          parent[nx][ny] = {u.x, u.y};
          pq.push({nx, ny, newDist});
        }
      }
    }
  }

  return -1LL;
}

void grid_clear(int R, int C) {
  for (int row = 1; row <= R; row++) {
    for (int col = 1; col <= C; col++) {
      parent[row][col] = {-1, -1};
      dis[row][col] = 1e18;
    }
  }
}

// Dynamically allocates memory based exactly on the current R and C
// values (sized to rows+1 / cols+1 to handle 1-based indexing cleanly).
void grid_resize_and_clear(int rows, int cols) {
  grid.assign(rows + 1, vector<int>(cols + 1, 0));
  dis.assign(rows + 1, vector<long long>(cols + 1, 1e18));
  parent.assign(rows + 1, vector<point>(cols + 1, {-1, -1}));
}

void solve(int tc) {
  cin >> R >> C;

  // Use grid_resize_and_clear (not grid_clear) if R/C can change between
  // test cases -- grid_clear alone doesn't resize the containers.
  grid_resize_and_clear(R, C);

  point src = {1, 1};
  point target = {R, C};

  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      cin >> grid[i][j];
    }
  }

  long long ans = dijkstra(src, target);

  if (ans == -1) {
    cout << -1 << '\n';
  } else {
    vector<point> path;
    point cur = target;
    // Compare fields individually: point has no operator!=, so
    // `cur != point{-1, -1}` would not compile.
    while (cur.x != -1 && cur.y != -1) {
      path.push_back(cur);
      cur = parent[cur.x][cur.y];
    }
    reverse(path.begin(), path.end());

    for (auto& step : path) cout << "(" << step.x << "," << step.y << ") ";

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
// - Check the problem's max rows/columns before fixing array sizes --
//   grids can be skewed (few rows & many columns, or vice versa).
