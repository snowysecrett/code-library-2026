// Time complexity: O(n log^2 n)
struct ImplicitBIT {
  map<int, int> bit;
  int n;
  ImplicitBIT() {}
  ImplicitBIT(int n) : n(n+5) {}
  void add(int x, int v) {
    x++;
    for (;x<n; x+=x&-x) bit[x] += v;
  }
  int sum(int x) {
    x++;
    int s = 0;
    for (;x;x-=x&-x) if (bit.count(x)) s += bit[x];
    return s;
  }
};
