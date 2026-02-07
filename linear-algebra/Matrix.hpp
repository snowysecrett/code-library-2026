struct Matrix {
  vector<vector<int>> a;
  int n;
  Matrix(int n_) {
    n = n_;
    a.resize(n);
    for (int i=0; i<n; i++) a[i].resize(n);
  }
  Matrix operator*(Matrix other) {
    Matrix product(n);
    for (int i=0; i<n; i++) {
      for (int k=0; k<n; k++) {
        if (!a[i][k]) continue;
        for (int j=0; j<n; j++) {
          if (!other.a[k][j]) continue;
          product.a[i][j] += a[i][k] * other.a[k][j];
          product.a[i][j] %= MOD;
        }
      }
    }
    return product;
  }
};
Matrix pow(Matrix b, int p) {
  if (p == 1) return b;
  Matrix r = pow(b, p >> 1);
  if (p & 1) return r * r * b;
  return r * r;
}
