struct SegTree1D {
  int n;
  vi st;
  void u(int l, int r, int tar, int idx, int val) {
    if (l == r) {
      st[idx] = val;
      return;
    }
    int mid = (l + r) >> 1;
    if (tar <= mid) u(l, mid, tar, (idx << 1) + 1, val);
    else u(mid + 1, r, tar, (idx << 1) + 2, val);
    st[idx] = max(st[(idx << 1) + 1], st[(idx << 1) + 2]);
  }
  int qu(int l, int r, int constl, int constr, int idx) {
    if (l <= constl && constr <= r) return st[idx];
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) return qu(l, r, mid + 1, constr, (idx << 1) + 2);
    else if (constr < l || r < mid + 1) return qu(l, r, constl, mid, (idx << 1) + 1);
    else {
      return max(qu(l, r, constl, mid, (idx << 1) + 1), qu(l, r, mid + 1, constr, (idx << 1) + 2));
    }
  }
  SegTree1D(int n) : n(n), st(4*n+20) {}
  void update(int i, int v) {
    u(0, n - 1, i, 0, v);
  }
  int query(int l, int r) {
    return qu(l, r, 0, n - 1, 0);
  }
};

struct SegTree2D {
  int n, m;
  vector<SegTree1D> st;
  void u(int l, int r, int tar, int col_tar, int idx, int val) {
    if (l == r) {
      st[idx].update(col_tar, val);
      return;
    }
    int mid = (l + r) >> 1;
    if (tar <= mid) u(l, mid, tar, col_tar, (idx << 1) + 1, val);
    else u(mid + 1, r, tar, col_tar, (idx << 1) + 2, val);
    int best = max(st[(idx << 1) + 1].query(col_tar, col_tar),
                 st[(idx << 1) + 2].query(col_tar, col_tar));
    st[idx].update(col_tar, best);
  }
  int qu(int l, int r, int constl, int constr, int l2, int r2, int idx) {
    if (l <= constl && constr <= r) return st[idx].query(l2, r2);
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) return qu(l, r, mid + 1, constr, l2, r2, (idx << 1) + 2);
    else if (constr < l || r < mid + 1) return qu(l, r, constl, mid, l2, r2, (idx << 1) + 1);
    else {
      return max(qu(l, r, constl, mid, l2, r2, (idx << 1) + 1), 
                 qu(l, r, mid + 1, constr, l2, r2, (idx << 1) + 2));
    }
  }
  SegTree2D(int n, int m) : n(n), m(m), st(4*n+20, SegTree1D(m)) {}
  void update(int i, int j, int v) {
    u(0, n - 1, i, j, 0, v);
  }
  int query(int u, int d, int l, int r) {
    return qu(u, d, 0, n - 1, l, r, 0);
  }
};
