struct DSU {
  vector<int> dsu, rank;
  int n;
  DSU() {}
  DSU(int n) : n(n), dsu(vi(n)), rank(vi(n)) {
    for (int i=0; i<n; i++) dsu[i] = i;
  }
  int set_of(int u) {
    while (dsu[u] != u) u = dsu[u];
    return u;
  }
  void Union(int u, int v) {
    u = set_of(u), v = set_of(v);
    if (u == v) return;
    if (rank[u] < rank[v]) swap(u, v);
    dsu[v] = u;
    if (rank[u] == rank[v]) rank[u]++;
  }
};
