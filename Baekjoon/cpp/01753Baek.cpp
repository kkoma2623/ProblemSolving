#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>

#define MAX_SIZE 20001

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

bool visit[MAX_SIZE];
int dist[MAX_SIZE];
int V, E, S;
vector<strt> G[MAX_SIZE];
priority_queue<strt, vector<strt>, greater<strt>>pq;

void dij(int v){
  while(!pq.empty()){
    strt curr = pq.top(); pq.pop();
    if(visit[curr.v]) continue;
    visit[curr.v] = true;

    dist[curr.v] = curr.cost;
    for(int i=0; i<G[curr.v].size(); ++i){
      strt next = G[curr.v][i];
      if(visit[next.v]) continue;
      pq.push({next.v, dist[curr.v] + next.cost});
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  memset(dist, -1, sizeof(dist));

  cin >> V >> E >> S;
  for(int i=0; i<E; ++i){
    int u, v, w; cin >> u >> v >> w;
    G[u].push_back({v, w});
  }
  dist[S] = 0;
  pq.push({S, 0});
  dij(1);

  for(int i=1; i<=V; ++i){
    if(dist[i] == -1) {
      cout << "INF\n";
      continue;
    }
    cout << dist[i] << "\n";
  }

  return 0;
}