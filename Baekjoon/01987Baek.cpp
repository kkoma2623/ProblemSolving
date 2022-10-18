#include <iostream>
#include <map>

#define MAX_R 20
#define MAX_C 20

using namespace std;

int R, C;
char G[MAX_R+1][MAX_C+1];
map<char, bool> mm;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int maxi;

void getInputs(){
  cin >> R >> C;
  for(int y=1; y<=R; ++y){
    string temp; cin >> temp;
    for(int x=0; x<C; ++x){
      G[y][x+1] = temp[x];
    }
  }
}

bool isOutOfBound(int y, int x){
  return y < 1 || x < 1 || y > R || x > C;
}

void dfs(int y, int x, int cnt){
  maxi = max(cnt, maxi);

  for(int i=0; i<4; ++i){
    int ny = y + dir[i][0], nx = x + dir[i][1];
    if(isOutOfBound(ny, nx)) continue;
    char nextChar = G[ny][nx];
    if(mm[nextChar]) continue;

    mm[nextChar] = true;
    dfs(ny, nx, cnt+1);
    mm[nextChar] = false;
  }
}

void solve(){
  getInputs();
  mm[G[1][1]] = true;
  dfs(1, 1, 1);
  cout << maxi << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}