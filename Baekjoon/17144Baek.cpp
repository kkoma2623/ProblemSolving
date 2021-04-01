#include <iostream>
#include <vector>

#define MAX_N 50

using namespace std;

struct pos{
  int r, c;
};


int R, C, T;
int dustMap[MAX_N+1][MAX_N+1];
int scatteredMap[MAX_N+1][MAX_N+1];
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
pos upPos, downPos;

void getInput(){
  vector<pos> cleaner;
  cin >> R >> C >> T;
  for(int r=1; r<=R; ++r){
    for(int c=1; c<=C; ++c){
      cin >> dustMap[r][c];
      if(dustMap[r][c] == -1){
        cleaner.push_back({r, c});
      }
    }
  }
  upPos = cleaner[0];
  downPos = cleaner[1];
}

void copyDustMap(){
  for(int r=1; r<=R; ++r){
    for(int c=1; c<=C; ++c){
      scatteredMap[r][c] = dustMap[r][c];
    }
  }
}

void copyScatteredMap(){
  for(int r=1; r<=R; ++r){
    for(int c=1; c<=C; ++c){
      dustMap[r][c] = scatteredMap[r][c];
    }
  }
}

bool boundCheck(int r, int c){
  return (r < 1 || c < 1 || r > R || c > C);
}

void moveDust(){
  for(int r=1; r<=R; ++r){
    for(int c=1; c<=C; ++c){
      if(dustMap[r][c] == 0){
        // no dust
        continue;
      }

      const int dust = dustMap[r][c]/5;
      int scattered = 0;
      if(dust == 0){
        // no dust to move
        continue;
      }
      for(int i=0; i<4; ++i){
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];
        if(boundCheck(nr, nc)){
          // out of bound
          continue;
        }
        if(dustMap[nr][nc] == -1){
          // cleaner exist
          continue;
        }
        scatteredMap[nr][nc] += dust;
        scattered += dust;
      }
      scatteredMap[r][c] -= scattered;
    }
  }
}

void upClear(){
  int r = upPos.r;
  int c = upPos.c;
  scatteredMap[r-1][c] = 0;
  --r;
  while(r > 1){
    scatteredMap[r][c] = scatteredMap[r-1][c];
    --r;
  }
  // r = 1

  while(c < C){
    scatteredMap[r][c] = scatteredMap[r][c+1];
    ++c;
  }
  // r = 1, c = C

  while(r < upPos.r){
    scatteredMap[r][c] = scatteredMap[r+1][c];
    ++r;
  }
  // r = upPos.r, c = C

  while(1 < c){
    scatteredMap[r][c] = scatteredMap[r][c-1];
    --c;
  }
  // r = upPos.r, c = 1

  scatteredMap[r][c+1] = 0;
}

void downClear(){
  int r = downPos.r;
  int c = downPos.c;
  scatteredMap[r+1][c] = 0;
  ++r;

  while(r < R){
    scatteredMap[r][c] = scatteredMap[r+1][c];
    ++r;
  }
  // r = R

  while(c < C){
    scatteredMap[r][c] = scatteredMap[r][c+1];
    ++c;
  }
  // c = C;

  while(r > downPos.r){
    scatteredMap[r][c] = scatteredMap[r-1][c];
    --r;
  }
  // r = downPos.r
  
  while(c > 1){
    scatteredMap[r][c] = scatteredMap[r][c-1];
    --c;
  }
  // r = downPos.r, c = 1
  
  scatteredMap[r][c+1] = 0;
}

void clearDust(){
  upClear();
  downClear();
}

int countDust(){
  int cnt = 0;
  for(int i=1; i<=R; ++i){
    for(int j=1; j<=C; ++j){
      if(dustMap[i][j] == -1){
        continue;
      }
      if(dustMap[i][j]){
        cnt += dustMap[i][j];
      }
    }
  }

  return cnt;
}

void solve(){
  getInput();
  while(T--){
    copyDustMap();
    moveDust();
    clearDust();
    copyScatteredMap();
  }

  cout << countDust();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}