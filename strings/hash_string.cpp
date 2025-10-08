struct hash_string {
  // all indices are ZERO-BASED
  const int fac = 2017;
  const int MOD = 1734232211;
  vector<int> pau, ps;
  int n;
  void init(string s) {
    n = s.size();
    pau.push_back(1);
    for(int i=1; i<=n; i++) {
      pau.push_back((pau[i-1] * fac) % MOD);
    }
    ps.push_back(s[0]);
    for(int i=1; i<n; i++) {
      ps.push_back((ps[i-1] * fac + s[i]) % MOD);
    }
  }
  int eval(int l, int r) {
    return (ps[r] - (l == 0 ? 0 : (ps[l-1] * pau[r-l+1]) % MOD) + MOD) % MOD;
  }
  int get_hash() {
    return ps[n - 1];
  }
};
