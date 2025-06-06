#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> pick;

void dfs(int idx){
  if(pick.size() == m){
    for(int i=0; i<pick.size(); ++i){
      cout << pick[i] << " ";
    } cout << "\n";
    return ;
  }

  for(int i=1; i<=n; ++i){

    pick.push_back(i);
    dfs(idx+1);
    pick.pop_back();
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  dfs(1);

  return 0;
}