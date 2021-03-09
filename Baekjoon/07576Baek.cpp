#include <iostream>
#include <queue>
#define MAX_N 1000

using namespace std;

int box[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N];
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

struct tom{
  int row, col;
  int day;
};

queue<tom> q;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m; cin >> n >> m;
  for(int i=0; i<m; ++i){
    for(int j=0; j<n; ++j){
      cin >> box[i][j];
      if(box[i][j] == 1){
        visit[i][j] = true;
        q.push({i,j, 1});
      }
    }
  }

  while(!q.empty()){
    tom nTom = q.front(); q.pop();
    for(int i=0; i<4; ++i){
      int nRow = nTom.row+dir[i][0], nCol = nTom.col+dir[i][1];
      if(nRow<0 || nRow>=m || nCol<0 || nCol>=n || visit[nRow][nCol] || box[nRow][nCol] == -1) continue;
      box[nRow][nCol] = nTom.day+1;
      visit[nRow][nCol]=true;
      q.push({nRow, nCol, nTom.day+1});
    }
  }

  int maxNum = -1;
  for(int i=0; i<m; ++i){
    for(int j=0; j<n; ++j){
      if(box[i][j] == 0){
        cout << -1;
        return 0;
      }
      if(maxNum < box[i][j]) maxNum = box[i][j];
    }
  }

  cout << maxNum-1;

  return 0;
}