struct LinkedList {
  int n;
  bool cyclic;
  vi l, r;
  LinkedList(int n, bool cyclic = false) : n(n), cyclic(cyclic), l(n), r(n) {
    for (int i=0; i<n; i++) {
      r[i] = (i + 1) % n;
      l[i] = (i + n - 1) % n;
    }
    if (!cyclic) r[n-1] = -1, l[0] = -1;
  }
  void remove(int x) {
    if (l[x] != -1) r[l[x]] = r[x];
    if (r[x] != -1) l[r[x]] = l[x];
  }
  int left_of(int x) { return l[x]; }
  int right_of(int x) { return r[x]; }
};
