#include <iostream>
#include <climits>
#include <vector>

#define MAX_N 501
#define MAX_C LLONG_MAX

typedef long long ll;

using namespace std;
struct strt{
  int from, end;
  ll cost;
};

ll dist[MAX_N];
int N, M;
vector<strt> weight;

bool bellman(){
  for(int i=1; i<=N; ++i){
    for(int j=0; j<weight.size(); ++j){
      int from = weight[j].from;
      int end = weight[j].end;
      ll cost = weight[j].cost;

      if(dist[from] == MAX_C) continue;
      if(dist[end] > dist[from] + cost){
        dist[end] = dist[from] + cost;
      }
    }
  }

  for(int i=0; i<weight.size(); ++i){
    int from = weight[i].from;
    int end = weight[i].end;
    ll cost = weight[i].cost;

    if(dist[from] == MAX_C) continue;
    if(dist[end] > dist[from] + cost){
      return true;
    }
  }

  return false;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  for(int i=1; i<MAX_N; ++i){
    dist[i] = MAX_C;
  }

  cin >> N >> M;
  

  for(int i=0; i<M; ++i){
    int v, u, w; cin >> v >> u >> w;
    weight.push_back({v, u, w});
  }

  dist[1] = 0;
  bool hasCycle = bellman();

  if(hasCycle) {
    cout << "-1";

    return 0;
  }

  for(int i=2; i<=N; ++i){
    if(dist[i] == MAX_C){
      cout << "-1\n";
      continue;
    }
    cout << dist[i] << "\n";
  }

  return 0;
}