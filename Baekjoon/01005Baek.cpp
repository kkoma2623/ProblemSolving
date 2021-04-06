#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>

#define MAX_N 1000

using namespace std;

int T, N, K, W;
int buildTime[MAX_N+1];
int dime[MAX_N+1];

int totalTime[MAX_N+1];
vector<int> build[MAX_N+1];
vector<int> comeBuild[MAX_N+1];

void initResource(){
  memset(buildTime, 0, sizeof(buildTime));
  memset(dime, 0, sizeof(dime));
  memset(totalTime, 0, sizeof(totalTime));

  for(int i=0; i<=MAX_N; ++i){
    vector<int> ().swap(build[i]);
    vector<int> ().swap(comeBuild[i]);
  }
}

void getInput(){
  cin >> N >> K;
  initResource();
  for(int i=1; i<=N; ++i){
    cin >> buildTime[i];
  }
  for(int i=1; i<=K; ++i){
    int l, r; cin >> l >> r;
    build[l].push_back(r);
    comeBuild[r].push_back(l);
    ++dime[r];
  }

  cin >> W;
}

vector<int> topologySort(){
  vector<int> v;
  queue<int> q;
  bool visit[MAX_N+1];
  memset(visit, false, sizeof(visit));

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

    v.push_back(curr);
    for(auto next: build[curr]){
      --dime[next];
    }
    for(int i=1; i<=N; ++i){
      if(dime[i] == 0){
        q.push(i);
      }
    }
  }

  return v;
}

int calcTime(vector<int> v){
  for(auto curr: v){
    totalTime[curr] += buildTime[curr];
    int maxi = 0;
    for(auto come: comeBuild[curr]){
      maxi = max(maxi, totalTime[come]);
    }
    totalTime[curr] += maxi;
  }

  return totalTime[W];
}

void solve(){
  getInput();
  vector<int> topSort = topologySort();
  cout << calcTime(topSort);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> T;
  while(T--){
    solve();

    cout << "\n";
  }

  return 0;
}