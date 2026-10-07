struct Node {
  vector<int32_t> dq;
  int32_t ptr = 0;
  void ins(int candidate, int i, const function<double(int, int)> &f) {
    while (sz(dq) > 1 && f(dq[sz(dq) - 2], dq.back()) < f(dq.back(), candidate)) {
      dq.pop_back();
      if (ptr == sz(dq)) ptr--;
    }
    dq.pb(candidate);
  }
  int optimal(const function<double(int, int)> &f, const function<double(int, int)> &g, int i, int l, int r) {
    if (!sz(dq)) {
      for (int j=l; j<=r; j++) ins(j, i, f);
    }
    while (ptr > 0 && f(dq[ptr - 1], dq[ptr]) <= i) ptr--;
    while (ptr + 1 < sz(dq) && f(dq[ptr], dq[ptr + 1]) > i) ptr++;
    return dq[ptr];
  }
};

struct MonotonicRangeCHT {
  int n;
  function<double(int, int)> f; // f(j, k) - slope function
  function<int(int, int)> g;    // g(i, j) - dp calculation function
  vector<Node> st;
  int qu(int l, int r, int constl, int constr, int idx, int i) {
    if (l <= constl && constr <= r) {
      int j = st[idx].optimal(f, g, i, constl, constr);
      return g(i, j);
    }
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) return qu(l, r, mid+1, constr, (idx<<1) + 2, i);
    else if (constr < l || r < mid+1) return qu(l, r, constl, mid, (idx<<1) + 1, i);
    else {
      return max(
        qu(l, r, constl, mid, (idx<<1) + 1, i),
        qu(l, r, mid+1, constr, (idx<<1) + 2, i)
      );
    }
  }
  MonotonicRangeCHT(int n, function<double(int, int)> f, function<int(int, int)> g) 
    : n(n), st(4 * n + 10), f(std::move(f)), g(std::move(g)) {}
  int query(int l, int r, int i) {  // returns max with parameter i
    return qu(l, r, 0, n - 1, 0, i);
  }
};
