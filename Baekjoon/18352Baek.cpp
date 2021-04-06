#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 300000

using namespace std;

struct strt{
  int num;
  int dist;
};

vector<int> G[MAX_N+1];
vector<int> cities;
int dist[MAX_N+1];
int N, M, K, X;

void getInput(){
  cin >> N >> M >> K >> X;
  for(int i=0; i<M; ++i){
    int v, u; cin >> v >> u;
    G[v].push_back(u);
  }
}

void setDist(){
  queue<strt> q;
  q.push({X, 0});
  dist[X] = -1;
  for(auto n : G[X]){
    q.push({n, 1});
  }

  while(!q.empty()){
    strt curr = q.front(); q.pop();
    
    if(dist[curr.num]){
      continue;
    }
    if(curr.dist == K){
      cities.push_back(curr.num);
    }
    dist[curr.num] = curr.dist;
    for(auto n : G[curr.num]){
      q.push({n, curr.dist+1});
    }
  }
}

void solve(){
  getInput();
  setDist();
  if(cities.empty()){
    cout << -1;

    return;
  }

  sort(cities.begin(), cities.end());
  for(auto city : cities){
    cout << city << "\n";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}