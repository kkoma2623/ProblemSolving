#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

#define MAX_N 10001

using namespace std;

vector<int> G[MAX_N];
int aa = 1;
priority_queue<int, vector<int>, greater<int>> hacked;
bool visit[MAX_N];
int N, M;
int SS;

void clearQ(){
  while(!hacked.empty()){
    hacked.pop();
  }
}
void clearVisit(){
  memset(visit, false, sizeof(visit));
}

void dfs(int v){
  if(v == 0) return;
  if(visit[v]) return;

  visit[v] = true;
  ++SS;
  for(int i=0; i<G[v].size(); ++i){
    dfs(G[v][i]);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;
  for(int i=0; i<M; ++i){
    int a, b; cin >> a >> b;
    G[b].push_back(a);
  }

  int maxSize = 0;

  for(int i=1; i<=N; ++i){
    SS = 0;
    clearVisit();
    dfs(i);
    if(SS > maxSize){
      clearQ();
      hacked.push(i);
      maxSize = SS;
      continue;
    }
    if(SS == maxSize){
      hacked.push(i);
      continue;
    }
  }

  while(!hacked.empty()){
    int comp = hacked.top();
    cout << comp << "\n";
    hacked.pop();
  }

  return 0;
}