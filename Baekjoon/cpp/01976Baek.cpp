#include <iostream>
#include <vector>
#include <memory.h>

#define MAX_N 200

using namespace std;

int N, M;
int G[MAX_N+1][MAX_N+1];
int ds[MAX_N+1];
int dsCnt[MAX_N+1];
vector<int> cities;

int _find(int u){
  if(ds[u] == u){
    return u;
  }

  return _find(ds[u]);
}

void _union(int a, int b){
  int u = _find(a);
  int v = _find(b);

  if(u == v){
    return;
  }

  if(dsCnt[u] < dsCnt[v]){
    ds[u] = v;
    dsCnt[u] += dsCnt[v];
  } else{
    ds[v] = u;
    dsCnt[v] += dsCnt[u];
  }
}

void getInput(){
  cin >> N >> M;
  memset(dsCnt, 1, sizeof(dsCnt));
  for(int i=1; i<=N; ++i){
    ds[i] = i;
    for(int j=1; j<=N; ++j){
      cin >> G[i][j];
    }
  }

  for(int i=0; i<M; ++i){
    int temp; cin >> temp;
    cities.push_back(temp);
  }
}

void solve(){
  getInput();
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      if(G[i][j]){
        _union(i, j);
      }
    }
  }

  for(int i=0; i<cities.size()-1; ++i){
    if(_find(ds[cities[i]]) != _find(ds[cities[i+1]])){
      cout << "NO";

      return;
    }
  }

  cout << "YES";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}