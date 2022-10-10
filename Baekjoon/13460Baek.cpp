#include <iostream>
#include <queue>
#include <set>

#define MAX_N 10
#define MAX_M 10

using namespace std;

int N, M;
char G[MAX_M+1][MAX_N+1]; // y, x
struct pos{
  int y, x;
};
struct strt{
  int ry, rx;
  int by, bx;
  int cnt;

  bool operator==(const strt &cmp) const{
    return ry==cmp.ry && rx==cmp.rx && by==cmp.by && bx==cmp.bx;
  }

  bool operator<(const strt &cmp) const{
    if(ry != cmp.ry) return ry < cmp.ry;
    if(rx != cmp.rx) return rx < cmp.rx;
    if(by != cmp.by) return by < cmp.by;
    return bx < cmp.bx;
  }

  bool operator>(const strt &cmp) const{
    if(ry != cmp.ry) return ry > cmp.ry;
    if(rx != cmp.rx) return rx > cmp.rx;
    if(by != cmp.by) return by > cmp.by;
    return bx > cmp.bx;
  }
};
pos R, B, O;
queue<strt> q;
set<strt> s;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool moveB(int &ry, int &rx, int &by, int &bx, int dy, int dx);

void getInputs(){
  cin >> N >> M;
  string temp;
  for(int y=0; y<N; ++y){
    cin >> temp;
    for(int x=0; x<M; ++x){
      G[y][x] = temp[x];
      if(temp[x] == 'R'){
        R.y = y; R.x = x;
        G[y][x] = '.';
      }
      if(temp[x] == 'B'){
        B.y = y; B.x = x;
        G[y][x] = '.';
      }
      if(temp[x] == 'O'){
        O.y = y; O.x = x;
      }
    }
  }
}

bool moveR(int &ry, int &rx, int &by, int &bx, int dy, int dx){
  if(ry == O.y && rx == O.x) return false;
  int nextX = rx+dx, nextY = ry+dy;
  if(G[nextY][nextX] == '#') return false;
  if(G[nextY][nextX] == 'O') {
    ry += dy; rx += dx;
    return false;
  }
  if(nextY == by && nextX == bx){
    if(!moveB(ry, rx, by, bx, dy, dx)){
      return false;
    }
  }
  ry += dy; rx += dx;
  return true;
}

bool moveB(int &ry, int &rx, int &by, int &bx, int dy, int dx){
  if(by == O.y && bx == O.x){
    return false;
  }
  int nextY = by+dy, nextX = bx+dx;
  if(G[nextY][nextX] == 'O') {
    by += dy; bx += dx;
    return false;
  }
  if(G[nextY][nextX] == '#') return false;
  if(nextX == rx && nextY == ry){
    if(!moveR(ry, rx, by, bx, dy, dx)){
      return false;
    }
  }
  by += dy; bx += dx;
  return true;
}

void printG(){
  for(int y=0; y<M; ++y){
    for(int x=0; x<N; ++x){
      if(x == R.x && y == R.y) {
        cout << 'R';
        continue;
      }
      if(x == B.x && y == B.y) {
        cout << 'B';
        continue;
      }
      cout << G[y][x];
    }
    cout << "\n";
  }
}

void solve(){
  getInputs();
  q.push({R.y, R.x, B.y, B.x, 0});
  s.insert({R.y, R.x, B.y, B.x});
  int ans = -1;
  while(!q.empty()){
    strt curr = q.front(); q.pop();
    if(curr.cnt > 10) break;
    if(curr.ry == O.y && curr.rx == O.x){
      if(curr.by != O.y || curr.bx != O.x){
      R = {curr.ry, curr.rx}; B = {curr.by, curr.bx};
        ans = curr.cnt;
        break;
      }
    }
    for(int i=0; i<4; ++i){
      int dirY = dir[i][1], dirX = dir[i][0];
      int ry = curr.ry, rx = curr.rx, by = curr.by, bx = curr.bx, cnt = curr.cnt;
      while(moveR(ry, rx, by, bx, dirY, dirX)){}
      while(moveB(ry, rx, by, bx, dirY, dirX)){}
      strt temp = {ry, rx, by, bx, curr.cnt+1};
      if(s.find(temp) != s.end()) continue;
      s.insert({ry, rx, by, bx, curr.cnt+1});
      q.push({ry, rx, by, bx, curr.cnt+1});
    }
  }

  cout << ans << "\n";
  // printG();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}