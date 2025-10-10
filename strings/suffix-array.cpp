struct super_string {
  vector<int> pos;
  vector<int> SA;
  vector<int> LCP;
  void suffix_array(string s) {
    int n = s.size();
    int k = 0, a, b;
    vector<int> x(s.begin(), s.end());
    vector<int> y(n);
    int lim = 128;
    vector<int> ws(max(n, lim));
    SA = LCP = y;
    iota(SA.begin(), SA.end(), 0);
    for (int j=0, p=0; p<n; j=max(1ll, j*2), lim=p) {
      p=j, iota(y.begin(), y.end(), n-j);
      for (int i=0; i<n; i++) {
        if (SA[i] >= j) y[p++] = SA[i] - j;
      }
      fill(ws.begin(), ws.end(), 0);
      for (int i=0; i<n; i++) {
        ws[x[i]]++;
      }
      for (int i=1; i<lim; i++) {
        ws[i] += ws[i-1];
      }
      for (int i=n; i--;) SA[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[SA[0]] = 0;
      for (int i=1; i<n; i++) {
        a = SA[i-1], b = SA[i];
        x[b] = (y[a] == y[b] && y[a+j] == y[b+j]) ? p-1 : p++;
      }
      for (int i=0, j; i<n-1; LCP[x[i++]] = k)
        for (k && k--, j=SA[x[i]-1]; s[i+k]==s[j+k]; k++);
    }
  }
  string s;
  vector<int> st[20];
  void init(string s_) {
    s = s_;
    s += "$";
    int len = s.size();
    pos.resize(len + 5);
    suffix_array(s);
    for (int i=0; i<SA.size(); i++) pos[SA[i]] = i;
    for (int i=0; i<20; i++) st[i].resize(len + 5);
    for (int i=0; i<LCP.size(); i++) st[0][i] = LCP[i];
    for (int i=1; i<20; i++) {
      for (int j=0; j+(1<<i)-1<LCP.size(); j++) {
        st[i][j] = min(st[i-1][j], st[i-1][j+(1<<(i-1))]);
      }
    }
  }
  int query_LCP(int x, int y) {
    if (x == y) return 1e9; // CHANGE if needed
    // lcp of s[x...], s[y...]
    int px = pos[x];
    int py = pos[y];
    if (px > py) swap(px, py);
    int l = px + 1, r = py;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(st[k][l], st[k][r-(1<<k)+1]);
  }
  int query_pos_LCP(int l, int r) {
    if (l == r) return 1e9; // CHANGE if needed
    l++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(st[k][l], st[k][r-(1<<k)+1]);
  }
};
