struct LinearBasis {
  int B = 0, sz = 1;
  vi has, basis;
  LinearBasis() {}
  LinearBasis(int B_): B(B_), has(vi(B_)), basis(vi(B_)) {}
  void insert(int x) {
    while (x) {
      int i = 31 - __builtin_clz(x);
      if (has[i]) x ^= basis[i];
      else {
        has[i] = 1, basis[i] = x;
        return;
      }
    }
  }
  bool count(int x) {
    while (x) {
      int i = 31 - __builtin_clz(x);
      if (has[i]) x ^= basis[i];
      else return 0;
    }
    return 1;
  }
  int max() {
    int ret = 0;
    for (int i=B-1; i>=0; i--) {
      if (!(ret & (1 << i)) && has[i]) {
        ret ^= basis[i];
      }
    }
    return ret;
  }
  void merge(LinearBasis other) {
    assert(B == other.B);
    for (int i=0; i<B; i++) {
      if (other.has[i]) insert(other.basis[i]);
    }
  }
};
LinearBasis merge(LinearBasis x, LinearBasis y) {
  x.merge(y);
  return x;
}
