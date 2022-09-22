#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_V 1000

using namespace std;

int N, M;
vector<int> adj[MAX_V+1];
bool visited[MAX_V+1];
int cnt;

void getInputs(){
  cin >> N >> M;
  for(int i=0; i<M; ++i){
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

void bfs(int v){
  queue<int> q;
  q.push(v);
  visited[v] = true;
  while(!q.empty()){
    int currV = q.front(); q.pop();
    for(int i=0; i<adj[currV].size(); ++i){
      int nextV = adj[currV][i];
      if(visited[nextV]) continue;
      q.push(nextV);
      visited[nextV] = true;
    }
  }
}

void findConCom(){
  for(int v=1; v<=N; ++v){
    if(visited[v]) continue;
    bfs(v);
    ++cnt;
  }
}

void solve(){
  getInputs();
  findConCom();

  cout << cnt << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  solve();

  return 0;
}