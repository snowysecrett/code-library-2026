/*
 * Author: snowysecret
 * Description: a data structure that maintains a big number N
 * in base b and supports the following:
 * 1. Given (possibly negative) integers |x|, |y| ≤ n,
 * add x * b^y to N.
 * 2. Given k and assuming N >= 0, print the k-th digit of N.
 * 3. Check if N is positive, negative or equals to 0.
 * O(log n) amortized time for each operation. Idea: maintain
 * digits in the interval (-b, b) avoiding another chain of carries
 * when undoing an operation with a chain of carries.
 * Status: tested on CF1994G (but is not optimal approach for such problem)
 */
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
