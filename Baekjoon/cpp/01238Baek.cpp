#include <iostream>
#include <queue>

#define MAX_N 1000

using namespace std;

typedef long long ll;

int N, M, X;
ll G[MAX_N+1][MAX_N+1];
ll dist[MAX_N+1][MAX_N+1];

void getInput(){
  cin >> N >> M >> X;
  fill(dist[0], dist[MAX_N+1], (ll)987654321);
  while(M--){
    ll u, v, t;
    cin >> u >> v >> t;
    G[u][v] = t;
    dist[u][v] = t;
  }
}

void floyd(){
  for(int w=1; w<=N; ++w){
    for(int from = 1; from <= N; ++from){
      if(from == w){
        continue;
      }
      for(int end = 1; end <= N; ++end){
        if(from == end || end == w){
          continue;
        }
        if(dist[from][end] > dist[from][w] + dist[w][end]){
          dist[from][end] = dist[from][w] + dist[w][end];
        }
      }
    }
  }
}

void printFloyd(){
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cout << dist[i][j] << " ";
    }cout << "\n";
  }
}

void solve(){
  getInput();
  floyd();
  ll maxi = 0;
  for(int i=1; i<=N; ++i){
    if(dist[i][X] >= 987654321 || dist[X][i] >= 987654321){
      continue;
    }
    maxi = max(maxi, dist[i][X] + dist[X][i]);
  }
  // cout << "===============\n";
  // printFloyd();
  cout << maxi;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}