#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 32000

using namespace std;

int N, M;
int dime[MAX_N+1];
vector<int> G[MAX_N+1];

void getInput(){
  cin >> N >> M;
  while(M--){
    int l, r; cin >> l >> r;
    G[l].push_back(r);
    ++dime[r];
  }
}

void topologySort(){
  vector<int> vec;
  int curr;
  for(int i=1; i<=N; ++i){
    if(dime[i] == 0){
      curr = i;
      break;
    }
  }
  queue<int> q;
  q.push(curr);
  
  while(!q.empty()){
    int currNum = q.front(); q.pop();
    if(dime[currNum] < 0){
      continue;
    }
    
    dime[currNum] = -1;
    vec.push_back(currNum);

    for(auto nx: G[currNum]){
      --dime[nx];
    }

    for(int i=1; i<=N; ++i){
      if(dime[i] == 0){
        q.push(i);

        break;
      }
    }
  }

  for(auto v: vec){
    cout << v << " ";
  }
}

void solve(){
  getInput();
  topologySort();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}