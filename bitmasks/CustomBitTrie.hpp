struct BitTrie {
  int b;
  struct Node {
    int nxt[2], info;
    Node() {
      nxt[0] = nxt[1] = -1;
      info = 1e9;
    }
  };
  vector<Node> st;
  BitTrie(int b) {
    this->b = b;
    st.resize(1);
  }
  void add(int x, int id) {
    int cur = 0;
    for (int i=b-1; i>=0; i--) {
      st[cur].info = min(st[cur].info, id);
      int bit = (x & (1ll << i)) > 0;
      if (st[cur].nxt[bit] == -1) {
        st[cur].nxt[bit] = sz(st);
        st.push_back(Node());
      }
      cur = st[cur].nxt[bit];
    }
    st[cur].info = min(st[cur].info, id);
  }
  int query(int x, int v) {
    // Find the minimum index j such that x ^ a[j] <= v
    int cur = 0, ans = 1e9;
    for (int i=b-1; i>=0; i--) {
      for (int j=0; j<2; j++) {
        if (st[cur].nxt[j] == -1) {
          st[cur].nxt[j] = sz(st);
          st.push_back(Node());
        }
      }
      int tar = (v & (1ll << i)) > 0;
      int ts = (x & (1ll << i)) > 0;
      if (tar == 1) {
        ans = min(ans, st[st[cur].nxt[ts]].info);
      }
      cur = st[cur].nxt[tar ^ ts];
    }
    ans = min(ans, st[cur].info); // allow = v
    return ans;
  }
};
