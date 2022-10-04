#include <iostream>
#include <vector>

#define MAX_N 50000
#define MAX_M 10000

using namespace std;

int N, M;
int par[MAX_N+1], dep[MAX_N+1];
vector<int> child[MAX_N+1], G[MAX_N+1];

int LCA(int u, int v){
  if(dep[u] < dep[v]){
    int t = u;
    u = v;
    v = t;
  }
  while(dep[v] != dep[u]){
    u = par[u];
  }
  while(v != u){
    v = par[v];
    u = par[u];
  }

  return u;
}

void buildTree(int v, int parent, int depth){
  par[v] = parent;
  dep[v] = depth;
  for(int i=0; i<G[v].size(); ++i){
    int u = G[v][i];
    if(u == parent) continue;
    child[v].push_back(u);

    buildTree(u, v, depth+1);
  }
}

void getInput(){
  cin >> N;
  for(int i=0; i<N-1; ++i){
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  buildTree(1, -1, 0);
  cin >> M;
  for(int i=0; i<M; ++i){
    int u, v;
    cin >> u >> v;
    cout << LCA(u, v) << "\n";
  }
}

void solve(){
  getInput();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}