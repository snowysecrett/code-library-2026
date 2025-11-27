struct AhoCorasick {
  const static int K = 26;
  const static char first = 'a';
  struct node {
    int fail = 0;
    int terminal = 0; // terminal link: following fail links until reaching a terminal state
    int len = 0; // length of string that matches (exactly) this state
    bool output = false; // terminal state or not?
    vector<int> nxt = vector<int>(K, -1); // DFA transitions
    vector<int> failchild; // fail 樹 children, do any aggregates here
    int nmatches = 0;
  } emptynode;
  vector<node> v = {emptynode};
  void insert(string s) {
    int idx = 0, cnter = 0;
    for (char c: s) {
      if (v[idx].nxt[c - first] == -1) {
        v[idx].nxt[c - first] = v.size();
        v.push_back(emptynode);
        idx = v.size() - 1;
      }
      else {
        idx = v[idx].nxt[c - first];
      }
      v[idx].len = ++cnter;
    }
    v[idx].output = true;
    v[idx].nmatches++;
  }
  void build() {
    queue<int> q;
    for (int i=0; i<K; i++) {
      if (v[0].nxt[i] != -1) q.push(v[0].nxt[i]);
      else v[0].nxt[i] = 0;
    }
    while (q.size()) {
      int f = q.front();
      q.pop();
      for (int i=0; i<K; i++) {
        if (v[f].nxt[i] != -1) {
          v[v[f].nxt[i]].fail = v[v[f].fail].nxt[i];
          q.push(v[f].nxt[i]);
        }
        else v[f].nxt[i] = v[v[f].fail].nxt[i];
      }
      if (v[v[f].fail].output) v[f].terminal = v[f].fail;
      else v[f].terminal = v[v[f].fail].terminal;
      v[v[f].fail].failchild.push_back(f);
      v[f].nmatches += v[v[f].fail].nmatches;
    }
  }
  int size() {
    return v.size();
  }
};
