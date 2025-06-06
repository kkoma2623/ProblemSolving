#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 100000

using namespace std;

struct strt{
  int a, b, x;
};

int N, M, C;
vector<strt> G[MAX_N+1];
int dime[MAX_N+1];
int sessionTime[MAX_N+1];

void getInput(){
  cin >> N >> M >> C;
  for(int i=1; i<=N; ++i){
    int temp;
    cin >> temp;
    sessionTime[i] = temp;
  }
  for(int i=0; i<C; ++i){
    int a, b, x;
    cin >> a >> b >> x;
    ++dime[b];
    G[a].push_back({a, b, x});
  }
}

void topologySort(){
  queue<int> q;
  for(int i=1; i<=N; ++i){
    if(dime[i] == 0){
      q.push(i);
    }
  }
  while(!q.empty()){
    int currNum = q.front();
    q.pop();
    if(dime[currNum] < 0){
      continue;
    }
    dime[currNum] = -1;

    for(auto cInfo: G[currNum]){
      sessionTime[cInfo.b] = max(sessionTime[cInfo.b], sessionTime[currNum] + cInfo.x);
      --dime[cInfo.b];
      if(dime[cInfo.b] == 0){
        q.push(cInfo.b);
      }
    }
  }
}

void printSession(){
  for(int i=1; i<=N; ++i){
    cout << sessionTime[i] << "\n";
  }
}

void solve(){
  getInput();
  topologySort();
  printSession();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}