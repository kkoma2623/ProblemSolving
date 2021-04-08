#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 1000

using namespace std;

struct strt{
  int num;
  int semester;
};


int N, M;
vector<int> G[MAX_N+1];
int dimen[MAX_N+1];
int seme[MAX_N+1];

void getInput(){
  cin >> N >> M;
  while(M--){
    int bef, aft; cin >> bef >> aft;
    G[bef].push_back(aft);
    ++dimen[aft];
  }
}

void topologySort(){
  queue<strt> q;
  for(int i=1; i<=N; ++i){
    if(dimen[i] == 0){
      q.push({i, 1});
    }
  }

  int semester = 2;
  while(!q.empty()){
    strt curr = q.front(); q.pop();
    if(dimen[curr.num] < 0){
      continue;
    }

    dimen[curr.num] = -1;
    seme[curr.num] = curr.semester;

    for(auto node : G[curr.num]){
      // decrease dimension
      --dimen[node];
    }

    for(int i=1; i<=N; ++i){
      if(dimen[i] == 0){
        q.push({i, curr.semester + 1});
        seme[i] = curr.semester;
      }
    }
  }
}

void solve(){
  getInput();
  topologySort();
  for(int i=1; i<=N; ++i){
    cout << seme[i] << " ";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}