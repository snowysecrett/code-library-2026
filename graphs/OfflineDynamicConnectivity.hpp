// Uses MasterDSU.hpp
// ans stores the number of bipartite components in the current graph

struct OfflineDynamicConnectivity {
  int n, q;
  int ans; // # of bipartite components
  vector<vector<pii>> st;
  OfflineDynamicConnectivity(int n_, int q_) {
    n = n_;
    q = q_ + 4;
    st.resize(4 * q + 10);
    ans = n;
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
  MasterDSU rb;
  
  void dfs(int idx, int l, int r, vector<int> &v) {
    int rbcnt = 0, oldans = ans;
    for (pii x: st[idx]) {
      bool flag = 0;
      pii s1 = rb.set_of(x.fi), s2 = rb.set_of(x.se);
      if (s1.fi == s2.fi) {
        flag = 1;
      }
      if (!flag) {
        if (rb.isBipartite(x.fi) || rb.isBipartite(x.se)) ans--;
      }
      else {
        if (rb.isBipartite(x.fi)) {
          ans -= (s1.se == s2.se);
        }
      }
      rb.Union(x.first, x.second);
      rbcnt++;
    }
    if (l == r) {
      v[l] = ans;
    }
    else {
      int mid = (l + r) >> 1;
      dfs((idx<<1) + 1, l, mid, v);
      dfs((idx<<1) + 2, mid+1, r, v);
    }
    while (rbcnt--) {
      rb.rollback();
    }
    ans = oldans;
  }
  void addEdge(int u, int v, int l, int r) {
    assert(0 <= min(u, v) && max(u, v) < n);
    upd(l, r, 0, q, 0, {u, v});
  }
  vector<int> ansAll() { 
    rb = MasterDSU(n);
    vector<int> ans(q+1);
    dfs(0, 0, q, ans);
    return ans;
  }
};
