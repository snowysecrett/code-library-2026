/**
 * Author: snowysecret
 * Date: 2025-12-12
 * Source: snowysecret
 * Description: Apparently I would get this wrong at times.
 * Maintains median of set of numbers with add, remove operations.
 * Status: tested on CF 2128E.
 * Time: $O(n \log n)$.
 */
struct RunningMedian {
  multiset<int> small, big; // uses the convention |small| ≥ |big|
  void balance_sets() {
    while (small.size() > 1 + big.size()) {
      big.insert(*small.rbegin());
      small.erase(small.lower_bound(*small.rbegin()));
    }
    while (big.size() > small.size()) {
      small.insert(*big.begin());
      big.erase(big.lower_bound(*big.begin()));
    }
  }
  void add(int x) {
    if (small.empty()) small.insert(x);
    else if (x <= *small.rbegin()) small.insert(x);
    else big.insert(x);
    balance_sets();
  }
  void remove(int x) {
    if (big.count(x)) big.erase(big.lower_bound(x));
    else small.erase(small.lower_bound(x));
    balance_sets();
  }
  int LeftMedian() {
    if (small.empty() && big.empty()) return -1;
    return *small.rbegin();
  }
  int RightMedian() {
    if (small.empty() && big.empty()) return -1;
    if (small.size() > big.size()) return LeftMedian();
    return *big.begin();
  }
  void clear() {
    small.clear();
    big.clear();
  }
};
