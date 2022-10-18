#include <iostream>
#include <vector>

using namespace std;

int K;
vector<int> v;

void getInputs(){
  cin >> K;
  if(K == 0) return;

  while(!v.empty()){
    v.pop_back();
  }
  for(int i=0; i<K; ++i){
    int temp; cin >> temp;
    v.push_back(temp);
  }
}

void dfs(vector<int> &picked, int idx){
  if(picked.size() == 6){
    for(int i=0; i<6; ++i){
      cout << picked[i] << " ";
    }cout << "\n";
    return;
  }

  if(idx >= v.size()) return;

  picked.push_back(v[idx]);
  dfs(picked, idx+1);
  picked.pop_back();
  dfs(picked, idx+1);
}

bool solve(){
  getInputs();
  if(K == 0) return true;
  vector<int> temp;
  dfs(temp, 0);
  return false;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  while(!solve()){
    cout << "\n";
  };

  return 0;
}