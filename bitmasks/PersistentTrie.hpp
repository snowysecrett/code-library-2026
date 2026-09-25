struct PersistentTrie {
  static const int B = 31;
  struct node {
    int nxt[2], cnt;
    node() {
      cnt = 1;
      nxt[0] = nxt[1] = -1;
    }
  };
  vi roots;
  vector<node> st;
  int newroot() {
    roots.pb(sz(st));
    st.pb(node());
    return sz(st) - 1;
  }
  int newnode() {
    st.pb(node());
    return sz(st) - 1;
  }
  PersistentTrie() {
    newroot();
  }
  int kth_smallest(int x, int k, int ver) { // k-th smallest val ^ x
    int rt = roots[ver], answer = 0;
    for (int i=B-1; i>=0; i--) {
      int bit = (x & (1ll << i)) > 0;
      assert(rt != -1);
      if (st[rt].nxt[bit] == -1) {
        rt = st[rt].nxt[bit ^ 1];
        if (bit ^ 1) answer += (1ll << i);
      }
      else if (k <= st[st[rt].nxt[bit]].cnt) {
        rt = st[rt].nxt[bit];
        if (bit) answer += (1ll << i);
      }
      else {
        k -= st[st[rt].nxt[bit]].cnt;
        rt = st[rt].nxt[bit ^ 1];
        if (bit ^ 1) answer += (1ll << i);
      }
    }
    return answer ^ x;
  }
  void insert(int x) {
    int Old = roots.back();
    int New = newroot();
    st[New].cnt += st[Old].cnt;
    for (int i=B-1; i>=0; i--) {
      int bit = (x & (1ll << i)) > 0;
      st[New].nxt[bit ^ 1] = (Old == -1 ? -1 : st[Old].nxt[bit ^ 1]);
      st[New].nxt[bit] = newnode();
      New = st[New].nxt[bit];
      if (Old != -1) {
        Old = st[Old].nxt[bit];
        if (Old != -1) st[New].cnt += st[Old].cnt;
      }
    }
  }
};
