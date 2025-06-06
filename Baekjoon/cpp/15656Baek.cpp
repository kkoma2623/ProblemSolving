#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> pick;
vector<int> inputNum;

void dfs(int idx){
  if(pick.size() >= M) {
    for(int i=0; i<M; ++i)
      cout << pick[i] << " ";
    cout << "\n";
    return ;
  }

  for(int i=1; i<=N; ++i){
    pick.push_back(inputNum[i-1]);
    dfs(i);
    pick.pop_back();
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M;
  for(int i=0; i<N; ++i){
    int temp; cin >> temp;
    inputNum.push_back(temp);
  }
  sort(inputNum.begin(), inputNum.end());

  dfs(1);

  return 0;
}