#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> pick;
bool sel[8+1];

void dfs(int idx){
  if(pick.size() == m){
    for(int i=0; i<pick.size(); ++i){
      cout << pick[i] << " ";
    } cout << "\n";
    return ;
  }

  for(int i=1; i<=n; ++i){
    if(sel[i]) continue;

    pick.push_back(i);
    sel[i] = true;
    dfs(idx+1);
    pick.pop_back();
    sel[i] = false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;

  dfs(1);

  return 0;
}