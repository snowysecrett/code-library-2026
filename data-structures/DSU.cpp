struct DSU {
  vector<int> dsu, sz;
  int n;
  DSU() {}
  DSU(int n) : n(n), dsu(n), sz(n, 1) {
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
    if (sz[u] < sz[v]) swap(u, v);
    dsu[v] = u;
    sz[u] += sz[v];
    return true;
  }
};
