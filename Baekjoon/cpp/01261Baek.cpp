#include <iostream>
#include <queue>
#include <string>

#define MAX_N 101
#define MAX_W 987654321

using namespace std;

struct strt{
  int x, y;
};

int N, M;
int G[MAX_N][MAX_N];
int w[MAX_N][MAX_N];
int way4[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
queue<strt> q;

void getInput(){
  cin >> M >> N;

  for(int i=0; i<N; ++i){
    string str; cin >> str;
    for(int j=0; j<M; ++j){
      G[i][j] = str[j] - '0';
    }
  }
}

void initW(){
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      w[i][j] = MAX_W;
    }
  }
}

void printW(){
  cout << "\n=============================\n";
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      cout << w[i][j] << " ";
    }cout << "\n";
  }
}

int solve(){
  initW();
  q.push({0,0});
  w[0][0] = 0;

  while(!q.empty()){
    strt curr = q.front(); q.pop();
    for(int i=0; i<4; ++i){
      int nX = curr.x + way4[i][0], nY = curr.y + way4[i][1];
      if(nX < 0 || nY < 0 || nX >= N || nY >= M) continue;
      
      int currCnt = w[curr.x][curr.y];
      int nextCnt = G[nX][nY] + currCnt;
      int currNextCnt = w[nX][nY];
      if(nextCnt < currNextCnt){
        w[nX][nY] = nextCnt;
        q.push({nX, nY});
      }
    }
  }
  // printW();
  return w[N-1][M-1];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  getInput();
  cout << solve();
  return 0;
}