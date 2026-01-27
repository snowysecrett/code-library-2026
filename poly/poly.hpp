typedef vector<ll> vl;
struct poly : vl {
  static constexpr ll mod = (119 << 23) + 1, root = 62; // = 998244353
  // For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
  // and 483 << 21 (same root). The last two are > 10^9.
  poly(int n) : vl(n) {}
  poly(std::initializer_list<ll> x) : vl(all(x)) {}
  poly(vl v) : vl(all(v)) {}
  poly(int n, int v) : vl(n, v) {}
  poly(const poly &b) {
    this->clear();
    for (auto x : b) this->pb(x);
  }
  private:
  ll modpow(ll b, ll e, const ll mod = 998244353) const {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
      if (e & 1) ans = ans * b % mod;
    return ans;
  }
  ll modinv(ll b, const ll mod = 998244353) const {
    return modpow(b, mod - 2, mod);
  }
  void ntt(vl &a) const {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
      rt.resize(n);
      ll z[] = {1, modpow(root, mod >> s)};
      rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) ::swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
  }
  poly conv(const poly &a, const poly &b) const {
    if (a.empty() || b.empty()) return poly(0);
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
        n = 1 << B;
    int inv = modpow(n, mod - 2);
    poly L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n)
      out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    while (sz(out) > s) out.pop_back();
    return out;
  }
  public:
  poly operator+(const poly &b) const {
    poly res(max(sz(*this), sz(b)), 0);
    rep(i,0,sz(res)) {
      ll av = (i < sz(*this) ? (*this)[i] : 0);
      ll bv = (i < sz(b) ? b[i] : 0);
      res[i] = (av + bv >= mod ? av + bv - mod : av + bv);
    }
    return res;
  }
  poly operator-(const poly &b) const {
    poly res(max(sz(*this), sz(b)), 0);
    rep(i,0,sz(res)) {
      ll av = (i < sz(*this) ? (*this)[i] : 0);
      ll bv = (i < sz(b) ? b[i] : 0);
      res[i] = (av - bv < 0 ? av - bv + mod : av - bv);
    }
    return res;
  }
  poly operator*(const poly &b) const {
    return conv(*this, b);
  }
  poly operator*(const ll &b) const {
    poly res(sz(*this), 0);
    rep(i,0,sz(res)) res[i] = ((*this)[i] * b) % mod;
    return res;
  }
  poly& operator=(const poly& b) {
    if (this == &b) return *this;
    vl::operator=(b); 
    return *this;
  }
  poly& operator+=(const poly& b) { *this = *this + b; return *this; }
  poly& operator-=(const poly& b) { *this = *this - b; return *this; }
  poly& operator*=(const poly& b) { *this = *this * b; return *this; }
  poly& operator*=(const ll& b) { *this = *this * b; return *this; }
  poly modxk(int k) const {
    k = min(k, (int)this->size());
    return poly(vl(this->begin(), this->begin() + k));
  }
  poly deriv() const {
    if (this->empty()) return poly(0);
    poly res(max(0LL, (ll)this->size() - 1), 0);
    for (int i = 1; i < (int)this->size(); i++)
      res[i - 1] = (*this)[i] * i % mod;
    return res;
  }
  poly integ() const {
    poly res((int)this->size() + 1, 0);
    for (int i = 0; i < (int)this->size(); i++)
      res[i + 1] = (*this)[i] * modpow(i + 1, mod - 2) % mod;
    return res;
  }
  poly inv(int n) const { // requires (*this)[0] != 0
    assert(!this->empty() && (*this)[0] % mod != 0);
    poly r(vl{modpow((*this)[0], mod - 2)});
    for (int m = 1; m < n; m <<= 1) {
      poly f = this->modxk(m << 1);
      r = (r * (poly(vl{2}) - f * r)).modxk(m << 1);
    }
    return r.modxk(n);
  }
  poly ln(int n) const { // requires (*this)[0] == 1
    assert(!this->empty() && (*this)[0] % mod == 1);
    poly f = this->modxk(n);
    return (f.deriv() * f.inv(n - 1)).integ().modxk(n);
  }
  poly exp(int n) const {
    assert(this->empty() || (*this)[0] % mod == 0);
    poly g(vl{1});
    for (int m = 1; m < n; m <<= 1) {
      poly cur = this->modxk(m << 1);
      g = (g * (poly(vl{1}) - g.ln(m << 1) + cur)).modxk(m << 1);
    }
    return g.modxk(n);
  }
  // calculate this^k mod x^n
  poly pow(int k, int n) const {
    if (this->empty()) return *this;
    int lead = 0;
    while (lead < (int)this->size() && (*this)[lead] == 0) lead++;
    if (lead == (int)this->size() || lead * k >= n)
      return poly(n, 0);
    ll inv = modinv((*this)[lead]);
    poly f((int)this->size() - lead, 0);
    for (int i = lead; i < (int)this->size(); i++)
      f[i - lead] = (*this)[i] * inv % mod;
    poly res = (f.ln(n - lead * k) * k).exp(n - lead * k);
    poly ans(n, 0);
    ll coef = modpow((*this)[lead], k);
    for (int i = 0; i < (int)res.size(); i++)
      ans[i + lead * k] = res[i] * coef % mod;
    return ans;
  } 
  friend ostream& operator<<(ostream& os, const poly& p) {
    os << "(";
    for (int i=0; i<sz(p); i++) {
      os << p[i];
      if (i+1 < sz(p)) os << "x^" << i;
      if (i+1 < sz(p)) os << " + ";
    }
    os << ")";
    return os;
  }
};
