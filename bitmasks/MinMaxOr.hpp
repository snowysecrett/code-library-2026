struct MinOR {
  int b;
  vi vis;
  MinOR(int b) : b(b), vis(1<<b) {}
  void upd(int x) {
    x=(1<<b)-1-x;
    queue<int> q;
    q.push(x);
    while (q.size()) {
      int f = q.front(); q.pop();
      if (vis[f]) continue;
      vis[f] = 1;
      for (int i=0; i<b; i++) {
        if (f & (1<<i)) {
          if (!vis[f ^ (1<<i)]) q.push(f ^ (1<<i));
        }
      }
    }
  }
  int min(int x) {
    int ans = 0;
    for (int i=b-1; i>=0; i--) {
      if (x & (1<<i)) continue;
      if (vis[ans ^ (1<<i)]) ans ^= (1<<i);
    }
    return (ans ^ ((1 << b) - 1)) | x; 
  }
};
struct MaxOR {
  int b;
  vi vis;
  MaxOR(int b) : b(b), vis(1<<b) {}
  void upd(int x) {
    queue<int> q;
    q.push(x);
    while (q.size()) {
      int f = q.front(); q.pop();
      if (vis[f]) continue;
      vis[f] = 1;
      for (int i=0; i<b; i++) {
        if (f & (1<<i)) {
          if (!vis[f ^ (1<<i)]) q.push(f ^ (1<<i));
        }
      }
    }
  }
  int max(int x) {
    int ans = 0;
    for (int i=b-1; i>=0; i--) {
      if (x & (1<<i)) continue;
      if (vis[ans ^ (1<<i)]) ans ^= (1<<i);
    }
    return ans | x; 
  }
};
