/*
https://codeforces.com/problemset/problem/2041/I
Trie to support autocompletion requests
*/

#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1e6 + 10;
struct Trie2025 {
  const static int ALPHA = 94;
  int f(int x) { // function that converts character to id
    return x - 33;
  }
  struct node {
    vector<int> child = vector<int>(ALPHA, -1);
    int parent = -1;
    // question-specific ones
    int optimal_autocomplete = -1;
    int longest_autocomplete = -1;
    int len = 0;
    set<int> ids;
  } emptynode;
  int walk_id = 0;
  vector<node> v = {emptynode};
  int new_node(int parent_id) { // Creates a new node and returns its id
    int id = v.size();
    v.push_back(emptynode);
    v[id].parent = parent_id;
    v[id].len = v[parent_id].len + 1;
    return id;
  }
  void insert(string str, int id) {
    vector<int> seq;
    for (char c: str) seq.push_back(f(c));
    int cur = 0;
    for (int x: seq) {
      if (v[cur].child[x] == -1) {
        v[cur].child[x] = new_node(cur);
      }
      cur = v[cur].child[x];
    }
    v[cur].ids.insert(id);
    while (cur >= 0) {
      v[cur].optimal_autocomplete = (v[cur].ids.size() ? *v[cur].ids.begin() : -1);
      v[cur].longest_autocomplete = (v[cur].ids.size() ? v[cur].len : -1);
      for (int i=0; i<ALPHA; i++) {
        if (v[cur].child[i] != -1 && v[v[cur].child[i]].longest_autocomplete > v[cur].longest_autocomplete) {
          v[cur].longest_autocomplete = v[v[cur].child[i]].longest_autocomplete;
        }
      }
      for (int i=0; i<ALPHA; i++) {
        if (v[cur].child[i] != -1 && v[v[cur].child[i]].longest_autocomplete == v[cur].longest_autocomplete) {
          v[cur].optimal_autocomplete = v[v[cur].child[i]].optimal_autocomplete;
          break;
        }
      }
      cur = v[cur].parent;
    }
  }
  void erase(string str, int id) {
    vector<int> seq;
    for (char c: str) seq.push_back(f(c));
    int cur = 0;
    for (int x: seq) {
      if (v[cur].child[x] == -1) {
        v[cur].child[x] = new_node(cur);
      }
      cur = v[cur].child[x];
    }
    v[cur].ids.erase(id);
    while (cur >= 0) {
      v[cur].optimal_autocomplete = (v[cur].ids.size() ? *v[cur].ids.begin() : -1);
      v[cur].longest_autocomplete = (v[cur].ids.size() ? v[cur].len : -1);
      for (int i=0; i<ALPHA; i++) {
        if (v[cur].child[i] != -1 && v[v[cur].child[i]].longest_autocomplete > v[cur].longest_autocomplete) {
          v[cur].longest_autocomplete = v[v[cur].child[i]].longest_autocomplete;
        }
      }
      for (int i=0; i<ALPHA; i++) {
        if (v[cur].child[i] != -1 && v[v[cur].child[i]].longest_autocomplete == v[cur].longest_autocomplete) {
          v[cur].optimal_autocomplete = v[v[cur].child[i]].optimal_autocomplete;
          break;
        }
      }
      cur = v[cur].parent;
    }
  }
  void append(char c) {
    if (v[walk_id].child[f(c)] == -1) {
      v[walk_id].child[f(c)] = new_node(walk_id);
    }
    walk_id = v[walk_id].child[f(c)];
  }
  bool backspace() {
    if (walk_id == 0) return 0;
    walk_id = v[walk_id].parent;
    return 1;
  }
};
int n;
string targets[MAXN];
void solve(int tc) {
  cin >> n;
  Trie2025 tr;
  while (n--) {
    string optype;
    cin >> optype;
    if (optype == "add") {
      int id;
      cin >> id;
      cin >> targets[id];
      tr.insert(targets[id], id);
    }
    else if (optype == "delete") {
      int id;
      cin >> id;
      tr.erase(targets[id], id);
    }
    else if (optype == "append") {
      string str;
      cin >> str;
      for (char c: str) {
        tr.append(c);
      }
    }
    else {
      int c;
      cin >> c;
      while (c > 0) {
        c--;
        if (tr.backspace()) continue;
        break;
      }
    }
    cout << tr.v[tr.walk_id].optimal_autocomplete << "\n";
  }
}
int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t; 
  for(int i=1; i<=t; i++) solve(i);
}
/*
g++ -Wl,-stack_size,0x20000000 code3.cpp -std=c++17 -O2 -o code3 -fsanitize=address,undefined
./code3 < input.txt
*/


