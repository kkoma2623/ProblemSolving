#include <iostream>
#include <vector>

using namespace std;
int visit[1001];
int N, M;
vector<int> vec[1001];

void dfs(int v){
  if(visit[v]) return;

  visit[v] = true;
  for(int i=0; i<vec[v].size(); ++i){
    int next = vec[v][i];

    dfs(next);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M;

  for(int i=0; i<M; ++i) {
    int v, u;
    cin >> v >> u;
    vec[v].push_back(u);
    vec[u].push_back(v);
  }
  int ans = 0;

  for(int i=1; i<= N; ++i) {
    if(visit[i]) continue;

    ++ans;
    dfs(i);
  }

  cout << ans;
  return 0;
}