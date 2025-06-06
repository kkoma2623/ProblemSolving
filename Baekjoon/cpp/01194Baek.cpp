#include <iostream>
#include <string>
#include <queue>

#define MAX_N 50

using namespace std;

struct strt{
  int r, c;
  int cnt;
  int key;
};

int N, M;
int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
char board[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N][64];
strt minsik, dest;

void getInput(){
  cin >> N >> M;
  for(int i=0; i<N; ++i){
    string str = ""; cin >> str;
    for(int j=0; j<M; ++j){
      board[i][j] = str[j];
      if(str[j] == '0'){
        minsik = {i, j, 0, 0};
        board[i][j] = '.';
      }
      if(board[i][j] == '1'){
        dest = {i, j};
      }
    }
  }
}

bool checkBound(int r, int c){
  return r < 0 || c < 0 || r >= N || c >= M;
}

void bfs(){
  queue<strt> q;
  q.push(minsik);

  while(!q.empty()){
    strt curr = q.front();
    q.pop();
    // cout << curr.r << ", " << curr.c << ": " << curr.cnt << " - " << curr.key << "\n";
    if(board[curr.r][curr.c] == '1'){
      cout << curr.cnt;

      return;
    }
    if(board[curr.r][curr.c] >= 'A' && board[curr.r][curr.c] <= 'F'){
      int door = 1 << (board[curr.r][curr.c] - 'A');
      // cout << "At capital " << door << ", " << curr.key << "\n";
      // cout << ((door & curr.key) != door) << " ?\n";
      if((door & curr.key) != door){
        // cout << "continue\n";
        continue;
      }
    }
    if(visit[curr.r][curr.c][curr.key]){
      continue;
    }
    visit[curr.r][curr.c][curr.key] = true;
    
    for(int i=0; i<4; ++i){
      int nr = curr.r + dir[i][0];
      int nc = curr.c + dir[i][1];
      if(checkBound(nr, nc)){
        continue;
      }
      if(board[nr][nc] >= 'a' && board[nr][nc] <= 'f' ){
        int nextKey = curr.key | 1 << (board[nr][nc] - 'a');
        q.push({nr, nc, curr.cnt+1, nextKey});
        
        continue;
      }
      if(board[nr][nc] == '#'){
        continue;
      }

      q.push({nr, nc, curr.cnt+1, curr.key});
    }
  }

  cout << -1;
}

void solve(){
  getInput();
  bfs();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}