/*
 * xor_distrib(x, n) computes, in O(log x) time, the distribution of
 * values of (x XOR k), for 0 ≤ k ≤ n. Note that the distribution
 * is represented by a disjoint set of ranges [l, r], where each
 * distinct value in a range only appears once in the distribution.
 */
vector<pii> xor_distrib(int x, int n) {
  vi bits;
  while (x) {
    bits.pb(x & -x);
    x -= x & -x;
  }
  reverse(all(bits));
  vector<pii> ans;
  vector<pair<pii, int>> ranges;
  int acc = 0;
  int xval = 0;
  for (int b : bits) {
    int mod = 2 * b;
    if ((n + 1) % mod == 0) {
      ranges.pb({{acc, acc + n}, xval});
      n = -1;
      break;
    }
    if (n / mod > 0) {
      ranges.pb({{acc, acc + n / mod * mod - 1}, xval});
    }
    xval ^= b;
    acc += n / mod * mod;
    n %= mod;
    if (n / (mod / 2) > 0) {
      ranges.pb({{acc, acc + n / (mod / 2) * (mod / 2) - 1}, xval});
      acc += n / (mod / 2) * (mod / 2);
      n %= (mod / 2);
    }
  }
  if (n >= 0) {
    ranges.pb({{acc, acc + n}, xval});
  }
  for (auto z : ranges) {
    int L = z.fi.fi ^ z.se, R = z.fi.se ^ z.se;
    if (L > R) swap(L, R);
    ans.pb({L, R});
  }
  return ans;
}
