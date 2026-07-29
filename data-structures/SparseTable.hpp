template<typename T>
struct SparseTable {
  int n;
  vector<pair<T, int32_t>> st[20];
  SparseTable() {}
  SparseTable(vector<T> v) {
    n = sz(v);
    for (int i=0; i<20; i++) st[i] = vector<pair<T, int32_t>>(n);
    for (int i=0; i<n; i++) st[0][i] = {v[i], i};
    for (int i=1; i<20; i++) {
      for (int j=0; j+(1<<i)-1<n; j++) {
        st[i][j] = max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
      }
    }
  }
  T query_max(int l, int r) {
    int k = 31-__builtin_clz(r-l+1);
    return max(st[k][l], st[k][r-(1<<k)+1]).fi;
  }
  int32_t query_argmax(int l, int r) {
    int k = 31-__builtin_clz(r-l+1);
    return max(st[k][l], st[k][r-(1<<k)+1]).se;
  }
};
