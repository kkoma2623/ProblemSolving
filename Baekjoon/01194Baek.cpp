#include <iostream>
#include <string>
#include <queue>

#define MAX_N 50

using namespace std;

struct strt{
  int r, c;
  int cnt;
  char keys = 0;
};


int N, M;
int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
char board[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N][27];
strt minsik;

void getInput(){
  cin >> N >> M;
  for(int i=0; i<N; ++i){
    string str = ""; cin >> str;
    for(int j=0; j<M; ++j){
      board[i][j] = str[j];
      if(str[j] == '0'){
        minsik = {i, j, 0};
        board[i][j] = '.';
      }
    }
  }
}

bool checkBound(int r, int c){
  return r < 0 || c < 0 || r >= N || c >= M;
}

void removeDoor(char key){
  char door = key - 32;
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      if(door == board[i][j]){
        board[i][j] = '.';
        return;
      }
    }
  }
}

void initVisit(){
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      for(int k=0; k<26; ++k){
        visit[i][j][k] = false;
      }
    }
  }
}

void bfs(){
  queue<strt> q;
  q.push(minsik);

  while(!q.empty()){
    strt curr = q.front();
    q.pop();
    cout << curr.r << ',' << curr.c << ": " << curr.cnt << "\n";

    for(int i=0; i<26; ++i){
      visit[curr.r][curr.c][i] = curr.keys[i];
      cout << curr.keys[i] << ", ";
    }
    cout << "\n";
    visit[curr.r][curr.c][26] = true;

    char currChar = board[curr.r][curr.c];
    if(currChar == '1'){
      cout << curr.cnt;
      
      return;
    }
    if(currChar == '.'){
      for(int i=0; i<4; ++i){
        int nr = curr.r + dir[i][0];
        int nc = curr.c + dir[i][1];
        if(checkBound(nr, nc)){
          continue;
        }
        if(board[nr][nc] == '#'){
          continue;
        }

        bool cantGo = true;
        for(int i=0; i<26; ++i){
          if(!visit[nr][nc][i] && curr.keys[i]){
            cantGo = false;
            break;
          }
        }
        if(!visit[nr][nc][26]){
          cantGo = false;
        }
        if(cantGo){
          continue;
        }
        
        q.push({nr, nc, curr.cnt + 1});
      }
      
      continue;
    }
    if(currChar - 'A' >= 0 && currChar - 'A' < 26){
      // door
      if(!curr.keys[currChar-'A']){
        continue;
      }

      board[curr.r][curr.c] = '.';
      q.push({curr.r, curr.c, curr.cnt});
    }
    if(currChar - 'a' >= 0 && currChar - 'a' < 26){
      // key
      curr.keys[currChar - 'a'] = currChar;
      char temp[26];
      for(int i=0; i<26; ++i){
        temp[i] = curr.keys[i];
      }
      board[curr.r][curr.c] = '.';
      q.push({curr.r, curr.c, curr.cnt, *temp});
      // initVisit();
    }
  }

  cout << -1;
}

void solve(){
  getInput();
  bfs();
}

int main(){
  // ios::sync_with_stdio(false);
  // cin.tie(0);
  solve();

  return 0;
}