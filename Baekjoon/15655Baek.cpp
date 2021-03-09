#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> pick;
vector<int> inputNum;
bool sel[8+1];

void dfs(int idx){
  if(idx > N) return ;
  if(pick.size() >= M) {
    for(int i=0; i<M; ++i)
      cout << pick[i] << " ";
    cout << "\n";
    return ;
  }

  for(int i=0; i<N; ++i){
    if(sel[idx+i] == false){
      sel[idx+i] = true;
      pick.push_back(inputNum[idx+i-1]);
      dfs(idx+i);
      pick.pop_back();
      sel[idx+i] = false;
    }
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