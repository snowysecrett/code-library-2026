/*
 * Author: snowysecret
 * Description: Kruskal Reconstruction Tree (0-based nodes).
 * Construction runs in O(n log n) since the DSU used is the slow version.
 * calc() precomputes the info necessary to evaluate LCAs in O(n log n).
 * Verified on abc394_g.
 * Warning: on a graph of n nodes, this uses at least 176n int32_t's.
 */
struct KRT {
  int n;
  vi dsu, repr;
  vi l, r, par, payload;
  int rt;
  KRT(int n) : n(n), dsu(n), repr(n), l(2*n), r(2*n), par(2*n), payload(2*n) {
    for (int i=0; i<n; i++) dsu[i] = repr[i] = i;
    for (int i=0; i<2*n; i++) l[i] = -1, r[i] = -1, par[i] = -1, payload[i] = 0;
    rt = n-1;
  }
  int set_of(int u) {
    if (dsu[u] == u) return u;
    return dsu[u] = set_of(dsu[u]);
  }
  void Union(int u, int v, int w = 0) {
    if (set_of(u) == set_of(v)) return;
    ++rt;
    par[repr[set_of(u)]] = par[repr[set_of(v)]] = rt;
    l[rt] = repr[set_of(u)], r[rt] = repr[set_of(v)];
    dsu[set_of(u)] = set_of(v);
    repr[set_of(u)] = rt;
    payload[rt] = w;
  }
  vi euler, L, R, dep;
  bool done_calc = false;
  vector<pair<int32_t, int32_t>> st[22];
  void dfs(int node, int depth = 0) {
    euler.pb(node);
    dep[node] = depth;
    if (l[node] != -1) {
      dfs(l[node], depth + 1);
      euler.pb(node);
    }
    if (r[node] != -1) {
      dfs(r[node], depth + 1);
      euler.pb(node);
    }
  }
  void calc() {
    if (done_calc) return;
    L = vi(rt + 1);
    R = vi(rt + 1);
    dep = vi(rt + 1);
    dfs(rt);
    for (int i=0; i<22; i++) st[i] = vector<pair<int32_t, int32_t>>(sz(euler));
    for (int i=0; i<sz(euler); i++) R[euler[i]] = i;
    for (int i=sz(euler)-1; i>=0; i--) L[euler[i]] = i;
    for (int i=0; i<sz(euler); i++) st[0][i] = {dep[euler[i]], euler[i]};
    for (int i=1; i<22; i++) {
      for (int j=0; j+(1<<i)-1<sz(euler); j++) {
        st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
      }
    }
    done_calc = true;
  }
  
  // Calculates the weight of the edge that unites nodes x and y.
  int union_weight(int x, int y) {
    if (!done_calc) calc();
    int m1 = min(L[x], L[y]), m2 = max(R[x], R[y]);
    int k = 31 - __builtin_clz(m2 - m1 + 1);
    return payload[min(st[k][m1], st[k][m2 - (1 << k) + 1]).second];
  }
};
