#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> pick;

void dfs(int idx){
  if(idx > N+1) return;

  if(pick.size() == M){
    for(int i=0; i<M; ++i){
      cout << pick[i] << " ";
    } cout << "\n";
    return;
  }

  if(pick.size() < M) {
    pick.push_back(idx);
    dfs(idx+1);
    pick.pop_back();
  }
  dfs(idx+1);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;

  dfs(1);

  return 0;
}