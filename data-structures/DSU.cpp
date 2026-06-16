struct DSU {
  vector<int> dsu, sizes;
  int n;
  DSU() {}
  DSU(int n) : n(n), dsu(n), sizes(n, 1) {
    for (int i = 0; i < n; i++) dsu[i] = i;
  }
  int set_of(int u) {
    if (dsu[u] == u) return u;
    return dsu[u] = set_of(dsu[u]); // path compression
  }
  bool Union(int u, int v) {
    u = set_of(u);
    v = set_of(v);
    if (u == v) return false;
    if (sizes[u] < sizes[v]) swap(u, v);
    dsu[v] = u;
    sizes[u] += sizes[v];
    return true;
  }
};
