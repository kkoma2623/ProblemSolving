#include <iostream>
#include <string>
#include <queue>

#define MAX_N 51

using namespace std;

struct pos{
  int x, y;
  int cnt;
};


int R, C;
char tTub[MAX_N][MAX_N];
int tTubTime[MAX_N][MAX_N];
pos hogPos;
pos shelter;
int way[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int visited[MAX_N][MAX_N];
queue<pos> waterQ;
queue<pos> hogQ;

void floodTime(){
  char tempTub[MAX_N][MAX_N];
  for(int i=0; i<R; ++i){
    for(int j=0; j<C; ++j){
      tempTub[i][j] = tTub[i][j];
      tTubTime[i][j] = 2501;
    }
  }

  while(!waterQ.empty()){
    pos currPos = waterQ.front(); waterQ.pop();

    for(int i=0; i<4; ++i){
      int nX = currPos.x + way[i][0], nY = currPos.y + way[i][1];

      if(nX < 0 || nY < 0 || nX >= R || nY >= C) continue;
      if(tempTub[nX][nY] == 'D' || tempTub[nX][nY] == 'X' || tempTub[nX][nY] == '*') continue;
      
      tempTub[nX][nY] = '*';
      tTubTime[nX][nY] = currPos.cnt;
      waterQ.push({nX, nY, currPos.cnt + 1});
    }
  }
}

int bfs(){
  floodTime();

  while(!hogQ.empty()){
    char tempMap[MAX_N][MAX_N];

    pos currHogPos = hogQ.front(); hogQ.pop();
    if(visited[currHogPos.x][currHogPos.y]) continue;
    visited[currHogPos.x][currHogPos.y] = true;

    for(int i=0; i<4; ++i){
      pos nPos = {currHogPos.x + way[i][0], currHogPos.y + way[i][1], currHogPos.cnt + 1};

      // check bound
      if(nPos.x < 0 || nPos.y < 0 || nPos.x >= R || nPos.y >= C) continue;
      // check visited
      if(visited[nPos.x][nPos.y]) continue;

      // alive
      if(tTub[nPos.x][nPos.y] == 'D') return nPos.cnt;
      // can't go
      if(tTubTime[nPos.x][nPos.y] < nPos.cnt) continue;
      if(tTub[nPos.x][nPos.y] != '.') continue;
      
      hogQ.push({nPos.x, nPos.y, nPos.cnt});
    }
  }

  return 2501;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> R >> C;
  for(int r=0; r<R; ++r){
    string temp; cin >> temp;
    for(int c=0; c<C; ++c){
      tTub[r][c] = temp[c];
      if(temp[c] == '*'){
        waterQ.push({r, c, 0});
        tTubTime[r][c] = 1;
      } else if(temp[c] == 'S'){
        hogPos = {r, c, 0};
        tTub[r][c] = '.';
        hogQ.push({r, c, 0});
      }else if(temp[c] == 'D'){
        shelter = {r, c};
      }
    }
  }

  int ans = bfs();

  if(ans >= 2501){
    cout << "KAKTUS";
  } else{
    cout << ans;
  }

  return 0;
}