#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 100000

using namespace std;

int N;
struct edge{
  int v, w;

  bool operator<(const edge &cmp)const{
    return w < cmp.w;
  }
  bool operator>(const edge &cmp)const{
    return w > cmp.w;
  }
};
vector<edge> G[MAX_N+1];
bool visited[MAX_N+1];

void getInputs(){
  cin >> N;
  for(int i=0; i<N; ++i){
    int startV; cin >> startV;
    int u; cin >> u;
    while(u != -1){
      int w; cin >> w;
      G[startV].push_back({u, w});
      cin >> u;
    }
  }
}

pair<int, int> findEndV(int currV){
  int retV = currV;
  int maxi = 0;
  priority_queue<edge, vector<edge>, greater<edge>> pq;
  pq.push({currV, 0});
  visited[currV] = true;

  while(!pq.empty()){
    edge curr = pq.top(); pq.pop();
    if(curr.w > maxi){
      maxi = curr.w;
      retV = curr.v;
    }
    for(auto next: G[curr.v]){
      if(visited[next.v]) continue;
      pq.push({next.v, next.w + curr.w});
      visited[next.v] = true;
    }
  }

  return {retV, maxi};
}

void solve(){
  getInputs();
  pair<int, int> endV = findEndV(1);
  for(int i=1; i<=MAX_N; ++i){
    visited[i] = false;
  }
  pair<int, int> end2EndV = findEndV(endV.first);
  cout << end2EndV.second << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}