/**
 * Author: snowysecret
 * Date: Unknown
 * Source: snowysecret
 * Description: Min-cost max-flow, with Johnson's Algorithm support.
 *  Works even if costs are negative, but note that negative cost cycles are not supported.
 *  Same API as MinCostMaxFlow.h, assumes #define int long long.
 * Status: Faster than MinCostMaxFlow.h on HKOJ M1851 Driver.
 * Time: $O(F E \log(V))$ where F is max flow. 
 */
struct MCMFJohnson {
  struct edge {
    int to, cost, flow, revid; // reverse edge id in adjacency list
  };
  vector<vector<edge> > adj, adj2;
  int mc, mf;
  int n;
  public:
  MCMFJohnson(int n_) {
    n = n_ + 5;
    adj.resize(n);
  }
  void addEdge(int u, int v, int flow, int cost) {
    int au = adj[u].size();
    int av = adj[v].size();
    adj[u].push_back({v, cost, flow, av});
    adj[v].push_back({u, -cost, 0, au});
  }
  pair<int, int> maxflow(int s, int t) {
    mc = mf = 0;
    int h[n];
    for(int i=0; i<n; i++) h[i] = 0;
    while(1) {
      int dist[n];
      pair<int, int> pre[n];
      bool vis[n];
      priority_queue<pair<int, int>, vector<pair<int, int> > ,greater<pair<int, int> > > pq;
      for(int i=0; i<n; i++) {
        dist[i] = 1e15;
        vis[i] = 0;
      }
      dist[s] = 0;
      pq.push({0, s});
      while(pq.size()) {
        pair<int, int> t = pq.top(); pq.pop();
        if(!vis[t.second]) {
          vis[t.second] = 1;
          int idx = 0;
          for(edge x: adj[t.second]) {
            if(!vis[x.to] && x.flow > 0 && dist[x.to] > dist[t.second] + x.cost + h[t.second] - h[x.to]) {
              dist[x.to] = dist[t.second] + x.cost + h[t.second] - h[x.to];
              pre[x.to] = {t.second, idx};
              pq.push({dist[x.to], x.to});
            }
            idx++;
          }
        }
      }
      if(dist[t] == 1e15) break;

      int e = 1e15; 
      int cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; 
        int lo = adj[pv][bc].revid;
        e = min(e, adj[pv][bc].flow);
        cur = pv;
      }
      cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; 
        int lo = adj[pv][bc].revid; 
        adj[pv][bc].flow -= e;
        adj[cur][lo].flow += e;
        cur = pv;
      }
      mc += (dist[t] - (h[s] - h[t])) * e;
      mf += e;
      for(int i=0; i<n; i++) h[i] += dist[i];
    }
    return {mf, mc};
  }
};
