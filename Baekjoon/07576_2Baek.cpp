#include <iostream>
#include <queue>
#define MAX_N 1000

using namespace std;

int G[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int N, M;
struct pos{
  int r, c;
  int cost;
};
queue<pos> q;

void getInputs(){
  cin >> M >> N;
  for(int r=0; r<N; ++r){
    for(int c=0; c<M; ++c){
      cin >> G[r][c];
      if(G[r][c] == 1){
        q.push({r, c, 0});
        visited[r][c] = true;
      }
    }
  }
}

bool isOutOfBound(int r, int c){
  return r<0 || c< 0 || r>=N || c >= M;
}

bool hasZero(){
  for(int r=0; r<N; ++r){
    for(int c=0; c<M; ++c){
      if(G[r][c] == 0) return true;
    }
  }
  return false;
}

void printG(){
  for(int r=0; r<N; ++r){
    for(int c=0; c<M; ++c){
      cout << G[r][c] << " ";
    }cout << "\n";
  }
}

void bfs(){
  int maxi = 0;
  while(!q.empty()){
    pos curr = q.front(); q.pop();
    maxi = max(curr.cost, maxi);
    G[curr.r][curr.c] = curr.cost;
    if(curr.cost == 0) G[curr.r][curr.c] = 1;
    for(int i=0; i<4; ++i){
      pos next = {curr.r+dir[i][0], curr.c+dir[i][1], curr.cost + 1};
      if(isOutOfBound(next.r, next.c)) continue;
      if(visited[next.r][next.c]) continue;
      if(G[next.r][next.c] == -1) continue;
      q.push(next);
      visited[next.r][next.c] = true;
    }
  }

  // printG();

  if(!hasZero()){
    cout << maxi << "\n";
  } else {
    cout << "-1\n";
  }
}

void solve(){
  getInputs();
  bfs();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}