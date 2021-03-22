#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 1001

using namespace std;

struct strt{
  int v;
  int cost;
  
  bool operator<(const strt& st)const{
    return cost < st.cost;
  }
  bool operator>(const strt& st)const{
    return cost > st.cost;
  }
};


// bool operator<(const strt& lhs, const strt rhs){
//   return lhs.w < rhs.w;
// }

int visited[MAX_N];
priority_queue<strt, vector<strt>, greater<strt>> pq;
vector<strt> v[MAX_N];
int sCity, dCity;
int N, M;
int dist[MAX_N];

void dijk(){
  while(!pq.empty()){
    strt curr = pq.top(); pq.pop();
    if(visited[curr.v]) continue;
    visited[curr.v] = true;
    dist[curr.v] = curr.cost;

    for(int i=0; i<v[curr.v].size(); ++i){
      strt u = v[curr.v][i];
      if(visited[u.v]) continue;
      pq.push({u.v, u.cost + dist[curr.v]});
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;
  for(int i=0; i<M; ++i){
    int s, d, w; cin >> s >> d >> w;
    v[s].push_back({d, w});
  }
  cin >> sCity >> dCity;

  pq.push({sCity, 0});
  dijk();

  cout << dist[dCity];
  return 0;
}