/**
 * Author: snowysecret
 * Persistent segment tree that supports the following operations:
 * Suppose we are maintaining an array a[1], a[2], ..., a[n])
 * Ver[newest] = Ver[some_old_version] + (a[x] := y) operation on the old version
 * Sum(ver, l, r) : query the sum of l to r in version ver
 * Testing: done on ABC453G.
 */
struct PersistentSeg {
  struct node {
    int sum = 0;
    int lc = -1, rc = -1; // left and right children
  };
  vector<node> st;
  vi heads;
  int verid, nxtnode;
  int init_node() {
    ++nxtnode;
    while (sz(st) <= nxtnode) st.pb(node());
    return nxtnode;
  }
  int new_version() { 
    ++verid;
    heads.pb(init_node());
    return verid;
  }

  int qu(int l, int r, int constl, int constr, int idx) {
    if (l <= constl && constr <= r) return st[idx].sum;
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) return qu(l, r, mid + 1, constr, st[idx].rc);
    else if (constr < l || r < mid + 1) return qu(l, r, constl, mid, st[idx].lc);
    else return qu(l, r, constl, mid, st[idx].lc) + qu(l, r, mid+1, constr, st[idx].rc);
  }
  void u(int l, int r, int tar, int idx_og, int idx_new, int val) {
    if (l == r) {
      st[idx_new].sum = val;
      return;
    }
    int mid = (l + r) >> 1;
    if (tar <= mid) {
      st[idx_new].lc = init_node();
      st[idx_new].rc = st[idx_og].rc;
      u(l, mid, tar, st[idx_og].lc, st[idx_new].lc, val);
    }
    else {
      st[idx_new].lc = st[idx_og].lc;
      st[idx_new].rc = init_node();
      u(mid + 1, r, tar, st[idx_og].rc, st[idx_new].rc, val);
    }
    st[idx_new].sum = st[st[idx_new].lc].sum + st[st[idx_new].rc].sum;
  }
  void init(int l, int r, int idx) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    st[idx].lc = init_node();
    st[idx].rc = init_node();
    init(l, mid, st[idx].lc);
    init(mid + 1, r, st[idx].rc);
  }
  int n;
  PersistentSeg(int n) {
    this->n = n + 5;
    verid = 0;
    nxtnode = -1;
    heads.pb(init_node());
    init(0, this->n, heads[0]); // heads[0] = 0
  }
  int point_add(int ver, int id, int val) {
    int nw = new_version();
    u(0, n, id, heads[ver], heads[nw], val);
    return nw;
  }
  int query_sum(int ver, int l, int r) {
    return qu(l, r, 0, n, heads[ver]);
  }
};
