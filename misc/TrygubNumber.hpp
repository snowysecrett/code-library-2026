struct TrygubNumber {
  int base;
  map<int, int> digs;
  TrygubNumber() {}
  TrygubNumber(const int& base) : base(base) {}
  void add(int x, int y) {
    digs[y] += x;
    int t;
    do {
      t = digs[y] / base;
      digs[y+1] += t;
      digs[y] -= t * base;
      if (digs[y+1] == 0) digs.erase(y+1);
      if (digs[y] == 0) digs.erase(y);
      y++;
    } while (t);
  }
  int get(int k) { // assumes N >= 0
    auto it=digs.lower_bound(k);
    int ans=0;
    if(it!=digs.end()&&it->first==k) ans=it->second;
    if(it!=digs.begin()&&prev(it)->second<0) ans--;
    return (ans+base)%base;
  }
  int sign() {
    auto it = digs.rbegin();
    if (it == digs.rend()) return 0;
    pii x = *it;
    if (x.se < 0) return -1;
    return 1;
  }
  bool smaller_than(int n, int b) { // checks if N < n * base^b
    add(-n, b);
    int res = (sign() < 0);
    add(n, b);
    return res;
  }
};
