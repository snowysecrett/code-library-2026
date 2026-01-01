// MasterDSU: Bipartiteness + rollback
struct MasterDSU {
  vi dsu, rank, color, bipartite;
  stack<vi> history;
  int n;
  MasterDSU() {}
  MasterDSU(int n_) : n(n_+5), dsu(vi(n_+5)), rank(vi(n_+5)), color(vi(n_+5)), bipartite(vi(n_+5)) {
    for (int i=0; i<n; i++) dsu[i] = i, color[i] = 0, bipartite[i] = 1;
  }
  pii set_of(int u) {
    if (u != dsu[u]) {
      int parity = color[u];
      pii res = set_of(dsu[u]);
      dsu[u] = res.fi, color[u] = res.se;
      color[u] ^= parity;
    }
    return {dsu[u], color[u]};
  }
  void Union(int u, int v) {
    pii su = set_of(u), sv = set_of(v);
    u = su.fi, v = sv.fi;
    int x = su.se, y = sv.se;
    if (u == v) {
      if (x == y) bipartite[u] = 0;
      return;
    }
    if (rank[u] < rank[v]) swap(u, v);
    history.push({v, dsu[v], rank[v], color[v], bipartite[v], 
                  u, dsu[u], rank[u], color[u], bipartite[u]
    });
    dsu[v] = u;
    color[v] = x ^ y ^ 1;
    bipartite[u] &= bipartite[v];
    if (rank[u] == rank[v]) rank[u]++;
  }
  bool isBipartite(int v) {
    return bipartite[set_of(v).fi];
  }
  void rollback() { // rolls back the last SUCCESSFUL union operation
    if (history.empty()) {
      cerr << "DSURollback: history is empty so no rollback done\n";
      return;
    }
    vi tp = history.top(); history.pop();
    for (int i=0; i<10; i+=5) {
      dsu[tp[i]] = tp[i+1];
      rank[tp[i]] = tp[i+2];
      color[tp[i]] = tp[i+3];
      bipartite[tp[i]] = tp[i+4];
    }
  }
};
