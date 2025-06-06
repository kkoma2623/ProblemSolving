#include <iostream>
#include <map>
#include <queue>

#define MAX_N 100

using namespace std;

struct pos{
  int r, c;
  int height;
};

int N, M, R;
int originBoard[MAX_N+1][MAX_N+1];
int board[MAX_N+1][MAX_N+1];
map<char, pos> dir;

void setDir(){
  dir['E'] = {0, 1};
  dir['W'] = {0 , -1};
  dir['S'] = {1, 0};
  dir['N'] = {-1 , 0};
}

void getInput(){
  cin >> N >> M >> R;
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=M; ++c){
      cin >> originBoard[r][c];
    }
  }
}

bool checkBound(int r, int c){
  return (r < 1 || c < 1 || r > N || c > M);
}

int attack(){
  pos p; cin >> p.r >> p.c;
  char dirChar; cin >> dirChar;
  pos d = dir[dirChar];

  int score = 0;
  queue<pos> q;
  q.push({p.r, p.c, board[p.r][p.c]});
  while(!q.empty()){
    pos curr = q.front(); q.pop();
    if(checkBound(curr.r, curr.c)){
      continue;
    }
    if(board[curr.r][curr.c] == -1){
      continue;
    }
    board[curr.r][curr.c] = -1;
    ++score;
    
    for(int i=1; i<curr.height; ++i){
      int nr = curr.r + d.r*i;
      int nc = curr.c + d.c*i;
      if(checkBound(nr, nc)){
        continue;
      }
      if(board[nr][nc] == -1){
        continue;
      }
      q.push({nr, nc, board[nr][nc]});
    }
  }

  return score;
}

void defense(){
  pos p; cin >> p.r >> p.c;
  if(board[p.r][p.c] != -1){
    return;
  }

  board[p.r][p.c] = originBoard[p.r][p.c];
}

void copyOriginBoard(){
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=M; ++c){
      board[r][c] = originBoard[r][c];
    }
  }
}

void printBoard(){
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=M; ++c){
      if(board[r][c] == -1){
        cout << "F ";
      } else{
        cout << "S ";
      }
    }cout << "\n";
  }
}

void solve(){
  setDir();
  getInput();
  copyOriginBoard();
  int score = 0;
  while(R--){
    score += attack();
    defense();
  }

  cout << score << "\n";
  printBoard();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}