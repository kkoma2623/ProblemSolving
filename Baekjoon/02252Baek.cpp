#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 32000

using namespace std;

int N, M;
int dime[MAX_N + 1];
vector<int> v[MAX_N+1];
bool visit[MAX_N+1];

void getInput(){
  cin >> N >> M;
  while(M--){
    int l, r; cin >> l >> r;
    v[l].push_back(r);
    ++dime[r];
  }
}

vector<int> topologySort(){
  vector<int> ret;
  // find root
  queue<int> q;
  for(int i=1; i<=N; ++i){
    if(dime[i] == 0){
      q.push(i);
    }
  }

  while(!q.empty()){
    int curr = q.front(); q.pop();
    if(visit[curr]){
      continue;
    }
    visit[curr] = true;
    ret.push_back(curr);

    for(auto nx: v[curr]){
      --dime[nx];
      if(dime[nx] == 0){
        q.push(nx);
      }
    }
  }

  return ret;
}

void solve(){
  getInput();
  vector<int> vec = topologySort();

  for(auto student: vec){
    cout << student << " ";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}