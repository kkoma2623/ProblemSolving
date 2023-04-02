#include <iostream>
#include <queue>

#define MAX_N 1000
#define MAX_K 10

using namespace std;

struct pos{
  int r, c;
  int count;
  int crushed;

  bool operator<(const pos &cmp)const{
    return count < cmp.count;
  }
  bool operator>(const pos &cmp)const{
    return count > cmp.count;
  }
};

int N, M, K;
int G[MAX_N+1][MAX_N+1];
bool visitG[MAX_N+1][MAX_N+1][MAX_K+1];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void getInputs(){
  cin >> N >> M >> K;
  for(int i=0; i<N; ++i){
    string temp; cin >> temp;
    for(int j=0; j<M; ++j){
      G[i][j] = temp[j]-'0';
      G[i][j] = temp[j]-'0';
    }
  }
}

bool isOutOfBound(int r, int c){
  return r < 0 || c < 0 || r >= N || c >= M;
}

int bfs(){
  pos curr = {0, 0, 0, 0};
  queue<pos> q;
  q.push(curr);

  while(!q.empty()){
    curr = q.front(); q.pop();
    if(visitG[curr.r][curr.c][curr.crushed]) continue;
    visitG[curr.r][curr.c][curr.crushed] = true;
    if(curr.r == N-1 && curr.c == M-1) return curr.count+1;

    for(int i=0; i<4; ++i){
      pos next = {curr.r + dir[i][0], curr.c + dir[i][1], curr.count + 1, curr.crushed};
      if(isOutOfBound(next.r, next.c)) continue;
      if(G[next.r][next.c] == 1 && next.crushed == K) continue;
      if(visitG[next.r][next.c][next.crushed]) continue;
      if(G[next.r][next.c] == 1){
        ++next.crushed;
        q.push(next);
        continue;
      }
      q.push(next);
    }
  }

  return -1;
}

void printV(){
  cout << "\n======================\n";
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      cout << visitG[i][j][0] << " ";
    }cout << "\n";
  }
  cout << "=================\n";

  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      cout << visitG[i][j][1] << " ";
    }cout << "\n";
  }
  cout << "======================\n";
}

void solve(){
  getInputs();
  int count = bfs();
  cout << count << "\n";
  // printV();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}