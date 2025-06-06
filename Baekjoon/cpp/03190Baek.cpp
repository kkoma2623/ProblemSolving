#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <queue>

#define MAX_N 100
#define APPLE 1

using namespace std;

int N, K;
int G[MAX_N+1][MAX_N+1];
struct direction{
  int t;
  char c;
};
struct pos{
  int r, c;
  bool operator<(const pos &cmp)const{
    if(r != cmp.r) return r < cmp.r;
    return c < cmp.c;
  }
  bool operator>(const pos &cmp)const{
    if(r != cmp.r) return r > cmp.r;
    return c > cmp.c;
  }
  bool operator==(const pos &cmp)const{
    return r == cmp.r && c == cmp.c;
  }
};
queue<direction> q;
deque<pos> snake;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
unsigned long long snakeDir = 0;
set<pos> snakeBodies;

void getInputs(){
  cin >> N >> K;
  snake.push_back({1, 1});
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      G[r][c] = 0;
    }
  }
  for(int i=0; i<K; ++i){
    int r, c; cin >> r >> c;
    G[r][c] = APPLE;
  }
  int dT; cin >> dT;
  while(dT--){
    int t;
    char c;
    cin >> t >> c;
    q.push({t, c});
  }
}

bool hitWall(int r, int c){
  return r <= 0 || c<= 0 || r > N || c > N;
}

void printG(){
  cout << "\n========\n";
  for(int r=1; r<N; ++r){
    for(int c=1; c<N; ++c){
      if(snakeBodies.find({r, c}) != snakeBodies.end()) {
        cout << "S ";
      } else if(G[r][c] == APPLE) cout << "* ";
      else cout << G[r][c] << " ";
    } cout << "\n";
  }
}

void moveSnake(){
  unsigned long long t = 0;
  snakeBodies.insert({1, 1});
  while(true){
    // printG();
    int dr = dir[snakeDir%4][0], dc = dir[snakeDir%4][1];
    pos curr = snake.front();
    if(hitWall(curr.r, curr.c)){
      cout << t << "\n";
      return;
    }
    
    ++t;
    pos next = {curr.r + dr, curr.c + dc};
    if(snakeBodies.find(next) != snakeBodies.end()){
      cout << t << "\n";
      return;
    }
    if(G[next.r][next.c] == APPLE){
      snake.push_front(next);
      snakeBodies.insert(next);
      G[next.r][next.c] = 0;
    } else {
      snake.push_front(next);
      snakeBodies.insert(next);
      snakeBodies.erase(snake.back());
      snake.pop_back();
    }
    if(t == q.front().t){
      char dirC = q.front().c; q.pop();
      if(dirC == 'L'){
        snakeDir += 3;
        snakeDir %= 4;
      }
      if(dirC == 'D'){
        snakeDir += 1;
        snakeDir %= 4;
      }
    }
  }
}

void solve(){
  getInputs();
  moveSnake();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}