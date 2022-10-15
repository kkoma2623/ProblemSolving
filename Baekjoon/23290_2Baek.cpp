#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define MAX_N 4

using namespace std;

int M, S;
// 0 ←, ↖, ↑, ↗, →, ↘, ↓, ↙
int fishDir[9][2] = {{0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
// 0 ↑, ←, ↓, →
int sharkDir[5][2] = {{0, 0}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int fishG[MAX_N+1][MAX_N+1][9];
int temp[MAX_N+1][MAX_N+1][9];
int copied[MAX_N+1][MAX_N+1][9];
int smellG[MAX_N+1][MAX_N+1];
int sharkY, sharkX;
bool visited[MAX_N+1][MAX_N+1];
int maxEat;
int sharkPath[3], tempPath[3];

void getInputs(){
  cin >> M >> S;
  for(int i=0; i<M; ++i){
    int y, x, d; cin >> y >> x >> d;
    ++fishG[y][x][d];
  }
  cin >> sharkY >> sharkX;
}

bool isOutOfBound(int y, int x){
  return y < 1 || x < 1 || y > MAX_N || x > MAX_N;
}

void copyfishG(){
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      for(int d=1; d<=8; ++d){
        temp[y][x][d] = 0;
        copied[y][x][d] = fishG[y][x][d];
      }
    }
  }
}

void moveFish(int y, int x, int d){
  bool changed = false;
  int ny = y, nx = x, nd = d;
  for(int i=0; i<=8; ++i){
    nd = d - i;
    if(nd < 1) nd += 8;
    ny = y + fishDir[nd][0];
    nx = x + fishDir[nd][1];

    if(sharkY == ny && nx == sharkX) continue;
    if(isOutOfBound(ny, nx)) continue;
    if(smellG[ny][nx] > 0) continue;
    changed = true;
    break;
  }
  if(changed){
    temp[ny][nx][nd] += fishG[y][x][d];
  } else {
    temp[y][x][d] += fishG[y][x][d];
  }
}

void moveFishes(){
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      for(int d=1; d<=8; ++d){
        if(fishG[y][x][d] <= 0) continue;
        moveFish(y, x, d);
      }
    }
  }
}

void backTracking(int y, int x, int idx, int eat){
  if(idx == 0){
    for(int y=1; y<=MAX_N; ++y){
      for(int x=1; x<=MAX_N; ++x){
        visited[y][x] = false;
      }
    }
    maxEat = -1;
  }
  if(idx == 3){
    if(maxEat >= eat) return;
    maxEat = eat;
    for(int i=0; i<3; ++i){
      sharkPath[i] = tempPath[i];
    }
    return;
  }

  for(int i=1; i<=4; ++i){
    int ny = y + sharkDir[i][0], nx = x + sharkDir[i][1];
    if(isOutOfBound(ny, nx)) continue;
    tempPath[idx] = i;
    if(visited[ny][nx]){
      backTracking(ny, nx, idx+1, eat);
    } else{
      int eatMore = 0;
      for(int d=1; d<=8; ++d){
        eatMore += temp[ny][nx][d];
      }
      visited[ny][nx] = true;
      backTracking(ny, nx, idx+1, eat+eatMore);
      visited[ny][nx] = false;
    }
  }
}

void moveShark(){
  backTracking(sharkY, sharkX, 0, 0);
  for(int i=0; i<3; ++i){
    int nextDirIdx = sharkPath[i];
    int ny = sharkY + sharkDir[nextDirIdx][0], nx = sharkX + sharkDir[nextDirIdx][1];
    for(int d=1; d<=8; ++d){
      if(temp[ny][nx][d] > 0){
        smellG[ny][nx] = 3;
      }
      temp[ny][nx][d] = 0;
    }
    sharkY = ny; sharkX = nx;
  }
}

void removeSmell(){
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      --smellG[y][x];
      if(smellG[y][x] < 0){
        smellG[y][x] = 0;
      }
    }
  }
}

void endCopy(){
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      for(int d=1; d<=8; ++d){
        fishG[y][x][d] = temp[y][x][d] + copied[y][x][d];
      }
    }
  }
}

long long countFishes(){
  long long ret = 0;
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      for(int d=1; d<=8; ++d){
        ret += fishG[y][x][d];
      }
    }
  }
  return ret;
}

void solve(){
  getInputs();
  for(int s=0; s<S; ++s){
    copyfishG();
    moveFishes();
    moveShark();
    removeSmell();
    endCopy();
  }
  cout << countFishes() << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}