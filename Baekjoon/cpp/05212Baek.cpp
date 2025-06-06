#include <iostream>
#include <vector>

#define MAX_N 10

using namespace std;

struct pos{
  int r, c;
};

char islandMap[MAX_N+1][MAX_N+1];
int R, C;
int uR = MAX_N, dR = 0, lC = MAX_N, rC = 0;
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
vector<pos> islandV;

void getInput(){
  cin >> R >> C;
  for(int r=0; r<R; ++r){
    for(int c=0; c<C; ++c){
      cin >> islandMap[r][c];
      if(islandMap[r][c] == 'X'){
        islandV.push_back({r, c});
      }
    }
  }
}

void setCorner(int r, int c){
  if(r < uR){
    uR = r;
  }
  if(r > dR){
    dR = r;
  }
  if(c < lC){
    lC = c;
  }
  if(c > rC){
    rC = c;
  }
}

bool willUnderSea(int r, int c){
  int cnt = 0;
  for(int i=0; i<4; ++i){
    int nr = r + dir[i][0];
    int nc = c + dir[i][1];
    if(nr < 0 || nc < 0 || nr >= R || nc >= C){
      ++cnt;
      continue;
    }

    if(islandMap[nr][nc] == '.'){
      ++cnt;
    }
  }

  return cnt >= 3;
}

void underSea(){
  vector<pos> v;
  
  for(auto &island : islandV){
    bool underSea = willUnderSea(island.r, island.c);
    if(underSea){
      v.push_back({island.r, island.c});
    }
  }
  
  // sank
  for(auto &p : v){
    islandMap[p.r][p.c] = '.';
  }
}

void cutMap(){
  for(int r=0; r<R; ++r){
    for(int c=0; c<C; ++c){
      if(islandMap[r][c] == 'X'){
        setCorner(r, c);
      }
    }
  }
}

void printIslandMap(){
  for(int r=uR; r<=dR; ++r){
    for(int c=lC; c<=rC; ++c){
      cout << islandMap[r][c];
    }cout << "\n";
  }
}

void solve(){
  getInput();
  underSea();
  cutMap();
  printIslandMap();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}