struct MinQueue {
  stack<int> s1, s2;
  stack<int> m1, m2;
  void push(int x) {
    s1.push(x);
    m1.push(m1.empty() ? x : min(x, m1.top()));
  }
  void pop() {
    if (s2.empty()) {
      while (s1.size()) {
        s2.push(s1.top());
        m2.push(m2.empty() ? s1.top() : min(m2.top(), s1.top()));
        s1.pop();
        m1.pop();
      }
    }
    m2.pop();
    s2.pop();
  }
  int size() {
    return s1.size() + s2.size();
  }
  int getmin() {
    if (m1.empty()) return m2.top();
    else if (m2.empty()) return m1.top();
    else return min(m1.top(), m2.top());
  }
};
