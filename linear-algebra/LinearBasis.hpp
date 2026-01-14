struct LinearBasis {
  int B = 31;
  vi has, basis;
  LinearBasis() {}
  LinearBasis(int B_): B(B_), has(vi(B_)), basis(vi(B_)) {}
  bool insert(int x) {
    while (x) {
      int i = 31 - __builtin_clz(x);
      if (has[i]) x ^= basis[i];
      else {
        has[i] = 1, basis[i] = x;
        return 1;
      }
    }
    return 0;
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
  int rank(int x) { 
    if (!count(x)) return -1;
    int ans = 0, sz = 1;
    for (int i=0; i<B; i++) if (has[i]) sz <<= 1;
    for (int i=B-1; i>=0; i--) {
      if (has[i]) {
        sz >>= 1;
        if (x & (1ll << i)) ans += sz;
      }
    }
    return ans + 1;
  }
  int kth(int k) {
    int sz = 1;
    for (int i=0; i<B; i++) if (has[i]) sz <<= 1;
    if (k < 1 || k > sz) return -1;
    int ans = 0;
    sz >>= 1;
    k--;
    for (int i=B-1; i>=0; i--) {
      if (has[i]) {
        if ((k & sz) && (ans & (1ll << i)) == 0) ans ^= basis[i];
        else if (!(k & sz) && (ans & (1ll << i))) ans ^= basis[i];
        sz >>= 1;
      }
    }
    return ans;
  }
};
LinearBasis merge(LinearBasis x, LinearBasis y) {
  x.merge(y);
  return x;
}
