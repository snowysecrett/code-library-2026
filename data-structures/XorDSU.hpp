struct XorDSU {
  vi id, col;
  vector<vi> sets;
  int cc;
  XorDSU(int n) {
    sets = vector<vi>(n);
    id = vi(n);
    col = vi(n);
    cc = n;
    for (int i=0; i<n; i++) id[i] = i, col[i] = 0, sets[i].pb(i);
  }
  bool Union(int u, int v, int x) { // O(log n): set a[u] ^ a[v] = x constraint
    if (id[u] == id[v]) {
      return (col[u] ^ col[v]) == x;
    }
    if (sets[id[u]].size() < sets[id[v]].size()) swap(u, v);
    int xval = col[u] ^ col[v] ^ x;
    int bruh = id[v];
    for (int x: sets[id[v]]) {
      sets[id[u]].pb(x);
      col[x] ^= xval;
      id[x] = id[u];
    }
    sets[bruh].clear();
    cc--;
    return 1;
  }
};
