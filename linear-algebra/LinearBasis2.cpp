struct XorBasis {
  int B;
  vector<int> have, basis;
  XorBasis(int B) : B(B), have(B), basis(B) {}
  int span() {
    int ans = 1;
    for (int x : have) {
      if (x == 1) ans <<= 1;
    }
    return ans;
  }
  bool count(int x) {
    if (x < 0 || x >= (1ll << B)) return 0;
    for (int i = B - 1; i >= 0; i--) {
      if (!(x & (1ll << i))) continue;
      if (have[i]) x ^= basis[i];
      else return 0;
    }
    return x == 0;
  }
  void insert(int x) {
    if (x < 0 || x >= (1ll << B)) {
      throw invalid_argument("insert(x) must have 0 <= x < 2^B");
    }
    for (int i = B - 1; i >= 0; i--) {
      if (x & (1ll << i)) {
        if (!have[i]) {
          have[i] = 1;
          basis[i] = x;
          return;
        }
        x ^= basis[i];
      }
    }
  }
  int rank(int x) { // rank(x) = 1 + number of elements in span < x
    if (!count(x)) {
      throw invalid_argument("attempt to fetch rank of x not in span");
    }
    int ans = 1, s = span();
    for (int i = B - 1; i >= 0; i--) {
      if (have[i]) {
        if (x & (1ll << i)) {
          ans += (s >> 1);
          x ^= basis[i];
        }
        s >>= 1;
      }
    }
    return ans;
  }
  int kth(int k) {
    int s = span();
    if (k < 1 || k > s) return -1;
    int cum_msk = 0;
    for (int i = B - 1; i >= 0; i--) {
      if (have[i]) {
        if (k > (s >> 1)) {
          k -= (s >> 1);
          if (!(cum_msk & (1ll << i))) {
            cum_msk ^= basis[i];
          }
        }
        else {
          if (cum_msk & (1ll << i)) {
            cum_msk ^= basis[i];
          }
        }
        s >>= 1;
      }
    }
    return cum_msk;
  }
};
