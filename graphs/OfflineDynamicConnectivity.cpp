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
struct OfflineDynamicConnectivity {
  int n, q;
  vector<vector<pii>> st;
  OfflineDynamicConnectivity(int n_, int q_) {
    n = n_;
    q = q_ + 4;
    st.resize(4 * q + 10);
  }
  void upd(int l, int r, int constl, int constr, int idx, pair<int, int> content) {
    if (l <= constl && constr <= r) {
      st[idx].push_back(content); return;
    }
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) upd(l, r, mid+1, constr, (idx<<1) + 2, content);
    else if (constr < l || r < mid+1) upd(l, r, constl, mid, (idx<<1) + 1, content);
    else {
      upd(l, r, constl, mid, (idx<<1) + 1, content);
      upd(l, r, mid+1, constr, (idx<<1) + 2, content);
    }
  }
  DSURollback rb;
  int cccnt;
  void dfs(int idx, int l, int r, vector<int> &v) {
    int rbcnt = 0;
    for (pii x: st[idx]) {
      if (rb.set_of(x.first) == rb.set_of(x.second)) continue;
      rb.Union(x.first, x.second);
      cccnt--;
      rbcnt++;
    }
    if (l == r) {
      v[l] = cccnt;
    }
    else {
      int mid = (l + r) >> 1;
      dfs((idx<<1) + 1, l, mid, v);
      dfs((idx<<1) + 2, mid+1, r, v);
    }
    while (rbcnt--) {
      rb.rollback();
      cccnt++;
    }
  }
  void addEdge(int u, int v, int l, int r) {
    assert(0 <= min(u, v) && max(u, v) < n);
    upd(l, r, 0, q, 0, {u, v});
  }
  vector<int> ansAll() { 
    rb = DSURollback(n);
    cccnt = n;
    vector<int> ans(q+1);
    dfs(0, 0, q, ans);
    return ans;
  }
};
