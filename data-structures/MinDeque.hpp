template<typename T>
struct MinDeque {
  stack<T> s[3], m[3];
  void push_util(int id, T x) {
    s[id].push(x);
    m[id].push(m[id].empty() ? x : min(x, m[id].top()));
  }
  void pop_util(int id) {
    s[id].pop();
    m[id].pop();
  }
  void push_back(T x) { push_util(0, x); }
  void push_front(T x) { push_util(1, x); }
  void rebalance(int i) {
    int tar = s[i].size() / 2;
    while (tar--) {
      push_util(2, s[i].top());
      pop_util(i);
    }
    while (s[i].size()) {
      push_util(i ^ 1, s[i].top());
      pop_util(i);
    }
    while (s[2].size()) {
      push_util(i, s[2].top());
      pop_util(2);
    }
  }
  void pop_front() {
    if (s[1].empty()) rebalance(0);
    pop_util(1);
  }
  void pop_back() {
    if (s[0].empty()) rebalance(1);
    pop_util(0);
  }
  T front() {
    if (s[1].empty()) rebalance(0);
    return s[1].top();
  }
  T back() {
    if (s[0].empty()) rebalance(1);
    return s[0].top();
  }
  int size() {
    return s[0].size() + s[1].size();
  }
  T getmin() {
    if (m[0].empty()) return m[1].top();
    else if (m[1].empty()) return m[0].top();
    else return min(m[0].top(), m[1].top());
  }
};
