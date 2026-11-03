struct Fraction {
  int p, q;
  Fraction(int p, int q) : p(p), q(q) {
    if (q < 0) this->p = -p, this->q = -q;
  }
  Fraction(int n = 0) : p(n), q(1) {}
  Fraction& operator=(const Fraction& other) {
    p = other.p;
    q = other.q;
    return *this;
  }
  Fraction& operator=(int n) {
    p = n;
    q = 1;
    return *this;
  }
  bool operator<(const Fraction& other) const {
    return p * other.q < q * other.p;
  }
  bool operator==(const Fraction& other) const {
    return p * other.q == q * other.p;
  }
  bool operator<=(const Fraction& other) const {
    return *this < other || *this == other;
  }
  friend ostream& operator<<(ostream& os, Fraction f) {
    return os << f.p << "/" << f.q;
  }
};
