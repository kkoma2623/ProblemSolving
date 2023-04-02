#include <iostream>
#include <vector>
#include <map>

#define MAX_V 20000

using namespace std;

int V, E;

void getInputs(vector<int> G[]){
  cin >> V >> E;
  for(int i=0; i<E; ++i){
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
}

bool searchTeam(vector<int> G[], int team[], int &startPos){
  int currTeam = 1;
  bool res = true;
  if(team[startPos] == 1) currTeam = 1;
  else if(team[startPos] == -1) currTeam = -1;
  else team[startPos] = currTeam;

  for(auto g: G[startPos]){
    if(team[g] == currTeam) return false;
    if(team[g] == -currTeam) continue;
    team[g] = -currTeam;
    res = searchTeam(G, team, g);
    if(!res) return false;
  }

  return true;
}

void solve(){
  vector<int> G[MAX_V+1];
  getInputs(G);
  int team[V+1];
  for(int i=1; i<=V; ++i) team[i] = 0;
  bool res = true;
  for(int i=1; i<=V; ++i){
    res = searchTeam(G, team, i);
    if(!res) break;
  }

  if(res) cout << "YES\n";
  else cout << "NO\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int K; cin >> K;
  while(K--){
    solve();
  }

  return 0;
}