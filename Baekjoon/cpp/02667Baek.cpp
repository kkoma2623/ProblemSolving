#include <iostream>
#include <string>

#define MAX_N 25

using namespace std;

int room[MAX_N+1][MAX_N+1];
bool visited[MAX_N+1][MAX_N+1];
bool colorVisited[MAX_N+1][MAX_N+1];
int n;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int groupNum;

bool boundCheck(int row, int col){
  return row<0 || row>=n || col<0 || col>=n;
}

void printVisit(){
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      cout << visited[i][j] << " ";
    }cout << "\n";
  }
}

void dfs(int row, int col, bool color){
  if(boundCheck(row, col)){
    return;
  }
  if(visited[row][col]){
    return;
  }

  if(color){
    if(room[row][col] == 0){
      return;
    }
    if(colorVisited[row][col]){
      return;
    }
    room[row][col] = groupNum;
    colorVisited[row][col] = true;
    for(int i=0; i<4; ++i){
      int nr = row + dir[i][0];
      int nc = col + dir[i][1];
      dfs(nr, nc, true);
    }
  } else{
    if(room[row][col] == 1 && !colorVisited[row][col]){
      room[row][col] = ++groupNum;
      for(int i=0; i<4; ++i){
        int nr = row + dir[i][0];
        int nc = col + dir[i][1];
        dfs(nr, nc, true);
      }
      colorVisited[row][col] = true;
    }
  }

  visited[row][col] = true;
  for(int i=0; i<2; ++i){
    int nr = row + dir[i][0];
    int nc = col + dir[i][1];
    dfs(nr, nc, false);
  }
}

void getInput(){
  cin >> n;
  for(int row=0; row<n; ++row){
    string temp; cin >> temp;
    for(int col=0; col<n; ++col){
      char tt = temp[col];
      room[row][col] = tt-'0';
    }
  }
  groupNum = 1;
}

void printRoom(){
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      cout << room[i][j] << " ";
    }cout << "\n";
  }
}

void solve(){
  getInput();
  dfs(0, 0, false);

  printRoom();
  cout << "\n===\n";
  printVisit();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}