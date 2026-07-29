struct SparseTable {
  int n;
  vector<pii> st[20];
  SparseTable(vi v) {
    n = sz(v);
    for (int i=0; i<n; i++) st[0][i] = {v[i], i};
    for (int i=1; i<20; i++) {
      for (int j=0; j+(1<<i)-1<n; j++) {
        st[i][j] = max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
      }
    }
  }
  int query_max(int l, int r) {
    int k = 31-__builtin_clz(r-l+1);
    return max(st[k][l], st[k][r-(1<<k)+1]).fi;
  }
  int query_argmax(int l, int r) {
    int k = 31-__builtin_clz(r-l+1);
    return max(st[k][l], st[k][r-(1<<k)+1]).se;
  }
};
