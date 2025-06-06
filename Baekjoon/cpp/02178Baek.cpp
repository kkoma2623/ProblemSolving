#include <iostream>
#include <string>
#include <queue>

#define MAX_N 100

using namespace std;

int maze[MAX_N][MAX_N];
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
struct stct {
  int row;
  int col;
  int step;
};


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m; cin >> n >> m;

  for(int i=0; i<n; ++i){
    string str; cin >> str;
    for(int j=0; j<m; ++j){
      maze[i][j] = str[j]-'0';
    }
  }

  queue<stct> q;
  q.push({0,0,1});

  while(!q.empty() && maze[n-1][m-1] <= 1){
    stct pos = q.front(); q.pop();
    int stepLen = pos.step;
    maze[pos.row][pos.col] = -1;
    for(int i=0; i<4; ++i){
      stct nPos = {pos.row+dir[i][0], pos.col+dir[i][1], stepLen+1};
      if(nPos.row < 0  || nPos.row >= n || nPos.col < 0 || nPos.col >= m || maze[nPos.row][nPos.col] > 1 || maze[nPos.row][nPos.col] == 0) continue;
      if(maze[nPos.row][nPos.col] == 1){
        q.push(nPos);
        maze[nPos.row][nPos.col] = stepLen+1;
      }
    }
  }

  cout << maze[n-1][m-1];

  return 0;
}