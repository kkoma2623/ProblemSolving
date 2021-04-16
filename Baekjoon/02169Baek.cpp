#include<iostream>

#define MAX_N 1000
#define MINCOST -987654321

using namespace std;

int N, M;
int board[MAX_N][MAX_N];
int cost[MAX_N][MAX_N][3];
bool visit[MAX_N][MAX_N];
int dir[3][2] = {{0, 1}, {0, -1}, {1, 0}};

void getInput(){
  cin >> N >> M;
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cin >> board[i][j];
    }
  }
}

int dfs(int r, int c, int d){
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      cout << "(";
      for(int k=0; k<3; ++k){
        cout << cost[i][j][k] << ", ";
      }
      cout << ")";
    }
    cout << "\n";
  }
  cout << "\n=============\n";
  if(r == N - 1 && c == M - 1){
    return board[r][c];
  }
  if(cost[r][c][d] != MINCOST){
    return cost[r][c][d];
  }

  visit[r][c] = true;

  int maxi = MINCOST;
  for(int i=0; i<3; i++){
    int nr = r + dir[i][0];
    int nc = c + dir[i][1];
    if(nr < 0 || nc < 0 || nr >= N || nc >= M){
      continue;
    }
    if(visit[nr][nc]){
      continue;
    }

    maxi = max(maxi, dfs(nr, nc, i));
  }
  visit[r][c] = false;
  cost[r][c][d] = board[r][c] + maxi;

  return cost[r][c][d];
}

void solve(){
  getInput();

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cost[i][j][0] = MINCOST;
      cost[i][j][1] = MINCOST;
      cost[i][j][2] = MINCOST;
    }
  }
  cout << dfs(0, 0, 0);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}