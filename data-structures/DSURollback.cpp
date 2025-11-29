struct DSURollback {
  vi dsu, rank;
  stack<vi> history;
  int n;
  DSURollback() {}
  DSURollback(int n_) : n(n_+5), dsu(vi(n_+5)), rank(vi(n_+5)) {
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
    history.push({v, dsu[v], u, rank[u]});
    dsu[v] = u;
    if (rank[u] == rank[v]) rank[u]++;
  }
  void rollback() { // rolls back the last SUCCESSFUL union operation
    if (history.empty()) {
      cerr << "DSURollback: history is empty so no rollback done\n";
      return;
    }
    vi tp = history.top(); history.pop();
    dsu[tp[0]] = tp[1];
    rank[tp[2]] = tp[3];
  }
};
