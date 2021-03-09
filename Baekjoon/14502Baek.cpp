#include <iostream>
#include <vector>
#define MAX_N 9

using namespace std;

int N, M;
int cell[MAX_N][MAX_N];
int localCell[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N];
int way4[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int ans = 0;
vector<pair<int, int>> zeroQ;
vector<pair<int, int>> virusQ;

void copyCell() {
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      localCell[i][j] = cell[i][j];
      visit[i][j] = false;
    }
  }
}

void dfs(int row, int col){
  if(row < 0 || row >=N || col < 0 || col >=M) return;

  for(int i=0; i<4; ++i){
    int nRow = row + way4[i][0];
    int nCol = col + way4[i][1];
    if(nRow < 0 || nRow >=N || nCol < 0 || nCol >=M) continue;
    if(visit[nRow][nCol]) continue;
    if(localCell[nRow][nCol] == 1) continue;

    visit[nRow][nCol] = true;
    localCell[nRow][nCol] = 2;
    dfs(nRow, nCol);
  }
}

void virus(int n) {
  if(n >= virusQ.size()) return;

  int row = virusQ[n].first, col = virusQ[n].second;
  visit[row][col] = true;

  dfs(row, col);

  return virus(n+1);
}

int countSafe() {
  int safe = 0;
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      if(localCell[i][j] == 0) ++safe;
    }
  }

  return safe;
}

void bfs(int i, int j, int k){

  for(int kk=k; kk<zeroQ.size(); ++kk){
    for(int jj=j; jj<kk; ++jj){
      for(int ii=i; ii<jj; ++ii){
        copyCell();
        localCell[zeroQ[ii].first][zeroQ[ii].second] = 1;
        localCell[zeroQ[jj].first][zeroQ[jj].second] = 1;
        localCell[zeroQ[kk].first][zeroQ[kk].second] = 1;
        virus(0);
        int safe = countSafe();
        ans = safe > ans ? safe : ans;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M;
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      cin >> cell[i][j];
      if(cell[i][j] == 0) {
        zeroQ.push_back({i,j});
        continue;
      }
      if(cell[i][j] == 2){
        virusQ.push_back({i,j});
      }
    }
  }

  bfs(0, 1, 2);

  cout << ans;

  return 0;
}