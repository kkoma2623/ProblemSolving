#include <iostream>
#include <vector>
using namespace std;

int dice[10];
vector<int> G[33], cost;
int dfs(int d){

  for(int j = 0; j < 4; ++j){

  }
}

int main(){
  cost.push_back(0);
  for(int j = 0; j < 20; ++j){
    G[j].push_back(j + 1);
    cost.push_back(j * 2 + 2);
  }
  G[5].push_back(20);
  // dfs 간단, (백업, 탐색, 복구), 파라미터로는 몇 번째 탐색이다.
  for(int j = 0; j < 10; ++j)
    cin >> dice[j];
  cout << dfs(0);
  return 0;
}