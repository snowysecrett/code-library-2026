/*
 * Author: snowysecret
 * Description: segment tree beats
 * Status: tested on LibChecker.
 */
struct SegtreeBeats {
  int stok;
  const ll extr = 2e18;
  struct node {
    ll max1, max2, maxc;
    ll min1, min2, minc;
    ll lazy, sum;
    int l, r;
  };
  vector<node> a;
  void pushtag_max(int idx, ll val) {
    if (val >= a[idx].max1) return;
    a[idx].sum -= (a[idx].max1 - val) * a[idx].maxc;
    a[idx].max1 = val;
    if (a[idx].l == a[idx].r) {
      a[idx].min1 = val;
    }
    else {
      if (a[idx].min1 >= val) {
        a[idx].min1 = val;
        a[idx].min2 = extr;
        a[idx].minc = a[idx].r - a[idx].l + 1;
      }
      else if (a[idx].min2 > val && a[idx].min2 != extr) {
        a[idx].min2 = val;
      }
    }
  }
  void pushtag_min(int idx, ll val) {
    if (val <= a[idx].min1) return;
    a[idx].sum += (val - a[idx].min1) * a[idx].minc;
    a[idx].min1 = val;
    if (a[idx].l == a[idx].r) {
      a[idx].max1 = val;
    }
    else {
      if (a[idx].max1 <= val) {
        a[idx].max1 = val;
        a[idx].max2 = -extr;
        a[idx].maxc = a[idx].r - a[idx].l + 1;
      }
      else if (a[idx].max2 < val && a[idx].max2 != -extr) {
        a[idx].max2 = val;
      }
    }
  }
  void pushtag_add(int idx, ll val) {
    a[idx].max1 += val;
    if (a[idx].max2 != -extr) a[idx].max2 += val;
    a[idx].min1 += val;
    if (a[idx].min2 != extr) a[idx].min2 += val;
    a[idx].lazy += val;
    a[idx].sum += val * (a[idx].r - a[idx].l + 1);
  }
  void pushdown(int idx) {
    if (a[idx].lazy) {
      pushtag_add((idx<<1)+1, a[idx].lazy);
      pushtag_add((idx<<1)+2, a[idx].lazy);
      a[idx].lazy = 0;
    }
    pushtag_max((idx<<1)+1, a[idx].max1);
    pushtag_max((idx<<1)+2, a[idx].max1);
    pushtag_min((idx<<1)+1, a[idx].min1);
    pushtag_min((idx<<1)+2, a[idx].min1);
  }
  void pushup(int idx) {
    ll max1, max2, maxc;
    ll min1, min2, minc;
    ll lazy, sum;
    ll l, r;
    a[idx].max1 = max(a[(idx<<1)+1].max1, a[(idx<<1)+2].max1);
    a[idx].max2 = (a[(idx<<1)+1].max1 == a[(idx<<1)+2].max1 ?
      max(a[(idx<<1)+1].max2, a[(idx<<1)+2].max2) :
      (a[(idx<<1)+1].max1 < a[(idx<<1)+2].max1 ?
      max(a[(idx<<1)+1].max1, a[(idx<<1)+2].max2) : 
      max(a[(idx<<1)+1].max2, a[(idx<<1)+2].max1)
    ));
    a[idx].maxc = (a[(idx<<1)+1].max1 == a[(idx<<1)+2].max1 ? 
      a[(idx<<1)+1].maxc + a[(idx<<1)+2].maxc :
      (a[(idx<<1)+1].max1 < a[(idx<<1)+2].max1 ? 
      a[(idx<<1)+2].maxc : a[(idx<<1)+1].maxc)
    );
    a[idx].min1 = min(a[(idx<<1)+1].min1, a[(idx<<1)+2].min1);
    a[idx].min2 = (a[(idx<<1)+1].min1 == a[(idx<<1)+2].min1 ?
      min(a[(idx<<1)+1].min2, a[(idx<<1)+2].min2) :
      (a[(idx<<1)+1].min1 > a[(idx<<1)+2].min1 ?
      min(a[(idx<<1)+1].min1, a[(idx<<1)+2].min2) : 
      min(a[(idx<<1)+1].min2, a[(idx<<1)+2].min1)
    ));
    a[idx].minc = (a[(idx<<1)+1].min1 == a[(idx<<1)+2].min1 ? 
      a[(idx<<1)+1].minc + a[(idx<<1)+2].minc :
      (a[(idx<<1)+1].min1 > a[(idx<<1)+2].min1 ? 
      a[(idx<<1)+2].minc :
      a[(idx<<1)+1].minc)
    );
    a[idx].sum = a[(idx<<1)+1].sum + a[(idx<<1)+2].sum;
  }
  void init1(int l, int r, int idx, ll val) {
    a[idx].l = l, a[idx].r = r;
    if(l == r) {
      a[idx].max1 = a[idx].min1 = val;
      a[idx].max2 = -extr;
      a[idx].min2 = extr;
      a[idx].maxc = a[idx].minc = 1;
      a[idx].lazy = 0;
      a[idx].sum = val;
      return;
    }
    int mid = (l+r) >> 1;
    init1(l, mid, (idx<<1)+1, val);
    init1(mid+1, r, (idx<<1)+2, val);
    pushup(idx);
  }
  void u1(int l, int r, int constl, int constr, int idx, ll v) {
    if (v >= a[idx].max1) return;
    if (l<=constl && constr<=r && v>a[idx].max2) {
      pushtag_max(idx, v); return;
    }
    pushdown(idx);
    int mid = (constl+constr) >> 1;
    if (mid < l || r < constl) u1(l, r, mid+1, constr, (idx<<1)+2, v);
    else if (constr < l || r < mid+1) u1(l, r, constl, mid, (idx<<1)+1, v);
    else {
      u1(l, r, constl, mid, (idx<<1)+1, v);
      u1(l, r, mid+1, constr, (idx<<1)+2, v);
    }
    pushup(idx);
  }
  void u2(int l, int r, int constl, int constr, int idx, ll v) {
    if (v <= a[idx].min1) return;
    if (l<=constl && constr<=r && v<a[idx].min2) {
      pushtag_min(idx, v); return;
    }
    pushdown(idx);
    int mid = (constl+constr) >> 1;
    if (mid < l || r < constl) u2(l, r, mid+1, constr, (idx<<1)+2, v);
    else if (constr < l || r < mid+1) u2(l, r, constl, mid, (idx<<1)+1, v);
    else {
      u2(l, r, constl, mid, (idx<<1)+1, v);
      u2(l, r, mid+1, constr, (idx<<1)+2, v);
    }
    pushup(idx);
  }
  void u3(int l, int r, int constl, int constr, int idx, ll v) {
    if (l <= constl && constr <= r) {
      pushtag_add(idx, v);
      return;
    }
    pushdown(idx);
    int mid = (constl+constr) >> 1;
    if (mid < l || r < constl) u3(l, r, mid+1, constr, (idx<<1)+2, v);
    else if (constr < l || r < mid+1) u3(l, r, constl, mid, (idx<<1)+1, v);
    else {
      u3(l, r, constl, mid, (idx<<1)+1, v);
      u3(l, r, mid+1, constr, (idx<<1)+2, v);
    }
    pushup(idx);
  }
  ll qu(int l, int r, int constl, int constr, int idx) {
    if(l <= constl && constr <= r) {
      return a[idx].sum;
    }
    pushdown(idx);
    int mid = (constl+constr) >> 1;
    if (mid < l || r < constl) return qu(l, r, mid+1, constr, (idx<<1)+2);
    else if (constr < l || r < mid+1) return qu(l, r, constl, mid, (idx<<1)+1);
    else {
      return qu(l, r, constl, mid, (idx<<1)+1) + qu(l, r, mid+1, constr, (idx<<1)+2);
    }
  }
  public:
  SegtreeBeats(int k) : stok(k), a(vector<node>(4*k + 10)) {
    init1(0, stok, 0, 0);
  }
  void range_chmin(int l, int r, ll v) { u1(l, r, 0, stok, 0, v); }
  void range_chmax(int l, int r, ll v) { u2(l, r, 0, stok, 0, v); }
  void range_add(int l, int r, ll v) { u3(l, r, 0, stok, 0, v); }
  ll query_sum(int l, int r) { return (ll) qu(l, r, 0, stok, 0); }
};
