#include <iostream>
#include <vector>

#define MAX_N 500
#define INF 987654321

using namespace std;

struct strt{
  int u;
  int cost;
};


int N, M, W;
int start;
// vector<strt> G[MAX_N+1];
int w[MAX_N+1][MAX_N+1];
int dist[MAX_N+1];


void getInput(){
  cin >> N >> M >> W;
  start = -1;
  fill(dist, dist + N + 1, INF);
  fill(w[0], w[MAX_N]+N+1, INF);
  // for(int i=0; i<N; ++i){
  //   vector<strt> temp;
  //   temp.swap(G[i]);
  // }
  for(int i=0; i<M; ++i){
    int S, E, T;
    cin >> S >> E >> T;
    start = S;
    w[S][E] = min(T, w[S][E]);
    w[E][S] = min(T, w[E][S]);
    // G[S].push_back({E, T});
    // G[E].push_back({S, T});
  }
  for(int i=0; i<W; ++i){
    int S, E, T;
    cin >> S >> E >> T;
    // G[S].push_back({E, -T});
    w[S][E] = min(w[S][E], -T);
  }
  
  dist[start] = 0;
  // for(auto g: G[start]){
  //   dist[g.u] = min(g.cost, dist[g.u]);
  // }
  for(int i=1; i<=N; ++i){
    dist[i] = w[start][i];
  }
}

void bellman(){
  for(int k=0; k<N; ++k){
    for(int mid=1; mid<=N; ++mid){
      for(int end=1; end<=N; ++end){
        if(dist[mid] == INF){
          continue;
        }
        dist[end] = min(dist[end], dist[mid]+w[mid][end]);
      }
    }
  }
    for(int mid=1; mid<=N; ++mid){
      for(int end=1; end<=N; ++end){
        if(dist[end] > dist[mid] + w[mid][end]){
          cout << "YES\n";
          return;
        }
      }
    }
  cout << "NO\n";
}

void solve(){
  int TC;
  cin >> TC;
  while(TC--){
    getInput();
    bellman();
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}