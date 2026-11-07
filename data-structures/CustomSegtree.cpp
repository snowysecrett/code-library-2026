template<class T>
struct SegTree {
  int n;
  vector<T> seg;
  function<T(const T&, const T&)> merge_op;
  SegTree(int n, function<T(const T&, const T&)> merge_op) : 
    n(n + 2), seg(4 * n + 20), merge_op(merge_op) {}
  void update(int i, T& v) { u(0, n, i, 0, v); }
  void update(int i, T&& v) { u(0, n, i, 0, v); }
  T query(int l, int r) { return qu(l, r, 0, n, 0); }

  private:
  void u(int l, int r, int tar, int idx, const T& v) {
    if (l == r) {
      seg[idx] = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (tar <= mid) u(l, mid, tar, (idx << 1) + 1, v);
    else u(mid + 1, r, tar, (idx << 1) + 2, v);
    seg[idx] = merge_op(seg[(idx << 1) + 1], seg[(idx << 1) + 2]);
  }
  T qu(int l, int r, int constl, int constr, int idx) {
    if (l <= constl && constr <= r) {
      return seg[idx];
    }
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) {
      return qu(l, r, mid+1, constr, (idx << 1) + 2);
    }
    else if (constr < l || r < mid+1) {
      return qu(l, r, constl, mid, (idx << 1) + 1);
    }
    else {
      return merge_op(qu(l, r, constl, mid, (idx << 1) + 1), 
                      qu(l, r, mid + 1, constr, (idx << 1) + 2));
    }
  }
};
