#include <iostream>
#include <vector>
#include <queue>
#define MAXV 100
using namespace std;
struct strt{
  int v, cost;
  bool operator<(const strt& st)const{
    return cost < st.cost;
  }
  bool operator>(const strt& st)const{
    return cost > st.cost;
  }
};
int dist[MAXV], V, E, S;
bool visit[MAXV];
vector<strt> G[MAXV];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> V >> E;
  for(int j = 0; j < E; ++j){
    int u, v, w; cin >> u >> v >> w;
    G[u].push_back({v, w});
    G[v].push_back({u, w}); // 양방향 간선
  }
  cin >> S; // 시작정점
  priority_queue<strt, vector<strt>, greater<strt>> pq;
  pq.push({S, 0});
  while(!pq.empty()){
    strt t = pq.top(); pq.pop();
    if(visit[t.v]) continue;
    visit[t.v] = true;
    dist[t.v] = t.cost;
    for(int j = 0; j < G[t.v].size(); ++j){
      strt u = G[t.v][j];
      if(visit[u.v]) continue;
      pq.push({u.v, dist[t.v] + u.cost});
    }
  }
  for(int j = 0; j < V; ++j){
    if(visit[j]) // 방문 가능
      cout << dist[j] << "\n";
    else // 방문 불가능
      cout << "INF\n";
  }
  return 0;
}