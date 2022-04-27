#include <iostream>
#include <vector>

#define MAX_N 500
#define INF 987654321

using namespace std;

int N, M;
struct strt{
  int from, to;
  long long w;
};
vector<strt> G;
long long dist[MAX_N+1];

void getInputs(){
  cin >> N >> M;
  for(int i=0; i<M; ++i){
    strt temp; cin >> temp.from >> temp.to >> temp.w;
    G.push_back(temp);
  }
}

void printDist(){
  for(int i=1; i<=N; ++i){
    cout << dist[i] << " ";
  }
  cout << "\n";
}

void bellman(){
  dist[1] = 0;
  for(int i=1; i<=N; ++i){
    for(auto g: G){
      if(dist[g.from] >= INF) continue;
      if(dist[g.to] > dist[g.from] + g.w){
        dist[g.to] = dist[g.from] + g.w;
      }
    }
  }
  for(auto g: G){
    
  }
  for(int i=2; i<=N; ++i){
    if(dist[i] >= INF) cout << -1 << "\n";
    else cout << dist[i] << "\n";
  }
}

void solve(){
  getInputs();
  bellman();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}