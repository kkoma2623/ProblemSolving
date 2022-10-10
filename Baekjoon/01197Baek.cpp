#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_E 100000

typedef long long ll;

using namespace std;

ll V, E;
ll djSet[MAX_E+1], djCnt[MAX_E+1]; // kruskal
vector<pair<ll, pair<ll, ll>> > edges; // cost, {u, v}

void initDjSet(){
  for(ll i=0; i<V; ++i){
    djSet[i] = i;
    djCnt[i] = 1;
  }
}

void getInput(){
  cin >> V >> E;
  for(ll i=0; i<E; ++i){
    ll u, v, cost;
    cin >> u >> v >> cost;

    edges.push_back({cost, {u, v}});
  }
}

ll _find(ll v){
  if(djSet[v] == v){
    return v;
  }
  return djSet[v] = _find(djSet[v]);
}

void _union(ll v1, ll v2){
  ll r1 = _find(v1);
  ll r2 = _find(v2);
  if(r1 == r2){
    return;
  }
  if(djCnt[r1] < djCnt[r2]){
    djSet[r1] = r2;
    djCnt[r2] += djCnt[r1];
  } else{
    djSet[r2] = r1;
    djCnt[r1] += djCnt[r2];
  }
}

ll kruskal(){
  ll ret = 0;
  sort(edges.begin(), edges.end());
  for(ll i=0, c=0; i<edges.size() && c<(V-1); ++i){
    ll cost = edges[i].first;
    ll u = edges[i].second.first;
    ll v = edges[i].second.second;
    
    if(_find(u) != _find(v)){
      _union(u, v);
      ret += cost;
      ++c;
    }
  }

  return ret;
}

void solve(){
  getInput();
  initDjSet();
  cout << kruskal() << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}