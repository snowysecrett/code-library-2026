// Uses Conv.hpp

class cmp {
  public:
  bool operator()(vl &x, vl &y) {
    return sz(x) > sz(y);
  }
};
typedef vector<vl> vvl;
vl multiconv(const vvl &v) {
  priority_queue<vl, vvl, cmp> pq;
  for (vl x: v) pq.push(x);
  while (pq.size() > 1) {
    vl x = pq.top(); pq.pop();
    vl y = pq.top(); pq.pop();
    pq.push(conv(x, y));
  }
  return pq.top();
}
