/**
 * Author: snowysecret
 * Date: 2026-09-24
 * Source: snowysecret
 * Description: segment tree that supports the following operations:
 * Range add, query min, query number of minimums.
 * Status: tested on CF 2128E.
 * Time: $O(n \log n)$.
 */
struct SegTreeMinimums {
  struct node {
    int mn = 0, lazy = 0, mncnt = 0;
  };
  vector<node> st;
  void build(int l, int r, int idx) {
    if(l == r) {
      st[idx].mn = 0;
      st[idx].mncnt = 1; 
      return;
    }
    int m = (l+r)>>1;
    build(l, m, (idx<<1)+1);
    build(m+1, r, (idx<<1)+2);
    st[idx].mncnt = r-l+1;
  }
  void push_down(int idx) {
    if(!st[idx].lazy) return;
    for(int i=(idx<<1)+1; i<=(idx<<1)+2; i++) {
      st[i].mn += st[idx].lazy;
      st[i].lazy += st[idx].lazy;
    }
    st[idx].lazy = 0;
  }
  void push_up(int idx) {
    st[idx].mn = min(st[(idx<<1)+1].mn, st[(idx<<1)+2].mn);
    st[idx].mncnt = (st[idx].mn == st[(idx<<1)+1].mn ? st[(idx<<1)+1].mncnt : 0)
                  + (st[idx].mn == st[(idx<<1)+2].mn ? st[(idx<<1)+2].mncnt : 0);
  }
  void u(int l, int r, int constl, int constr, int idx, int val) {
    if(l<=constl && constr<=r) {
      st[idx].mn += val;
      st[idx].lazy += val;
      return;
    }
    int mid = (constl+constr)>>1;
    push_down(idx);
    if(mid<l||r<constl) u(l,r,mid+1,constr,(idx<<1)+2,val);
    else if(constr<l||r<mid+1) u(l,r,constl,mid,(idx<<1)+1,val);
    else {
      u(l,r,constl,mid,(idx<<1)+1,val);
      u(l,r,mid+1,constr,(idx<<1)+2,val);
    }
    push_up(idx);
  }
  pair<int,int> qu(int l, int r, int constl, int constr, int idx) {
    if(l<=constl && constr<=r) return {st[idx].mn, st[idx].mncnt};
    int mid = (constl+constr) >> 1;
    push_down(idx);
    if(mid < l || r < constl) return qu(l, r, mid+1, constr, (idx<<1) + 2);
    else if(constr < l || r < mid+1) return qu(l, r, constl, mid, (idx<<1) + 1);
    else {
      pair<int, int> lc = qu(l, r, constl, mid, (idx<<1) +1 );
      pair<int, int> rc = qu(l, r, mid+1, constr, (idx<<1) + 2);
      int mm = min(lc.first, rc.first);
      int cnt = (lc.first == mm ? lc.second : 0) + (rc.first == mm ? rc.second : 0);
      return {mm, cnt};
    }
  }
  public:
  int stok;
  SegTreeMinimums(int k) : stok(k + 5) {
    st.resize(4 * stok);
    build(0, stok, 0);
  }
  void range_add(int l, int r, int v) {
    u(l, r, 0, stok, 0, v);
  }
  int query_mincnt(int l, int r) {
    pair<int, int> hi = qu(l, r, 0, stok, 0);
    return hi.second;
  }
  int query_min(int l, int r) {
    pair<int, int> hi = qu(l, r, 0, stok, 0);
    return hi.first;
  }
};
