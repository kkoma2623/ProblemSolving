#include <iostream>
#include <vector>

#define MAX_N 21

typedef unsigned long long ull;

using namespace std;

ull G[MAX_N+1][MAX_N+1];
ull tempG[MAX_N+1][MAX_N+1];
bool merged[MAX_N+1][MAX_N+1];
int N;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<vector<char>> v;
char alp[4] = {'L', 'R', 'U', 'D'};

void getInputs(){
  cin >> N;
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      cin >> G[y][x];
      tempG[y][x] = G[y][x];
    }
  }
}

void initMerged(){
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      merged[y][x] = false;
    }
  }
}

void backUps(){
  initMerged();
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      G[y][x] = tempG[y][x];
    }
  }
}

bool moveR(){
  bool ret = false;
  for(int y=N; y>0; --y){
    int currX = N;
    int nextX = N-1;
    while(nextX > 0){
      if(G[y][currX] == 0){
        while(nextX > 1 && G[y][nextX] == 0) --nextX;
        
        if(G[y][nextX] != 0) ret = true;
        G[y][currX] = G[y][nextX];
        G[y][nextX] = 0;
        currX = nextX;
        --nextX;
        continue;
      }
      while(nextX > 1 && G[y][nextX] == 0){
        --nextX;
      }
      if(G[y][currX] == G[y][nextX] && !merged[y][currX] && !merged[y][nextX]){
        G[y][currX] += G[y][nextX];
        G[y][nextX] = 0;
        merged[y][currX] = true;
        currX = nextX;
        --nextX;
        ret = true;
        continue;
      }
      if(currX-1 == nextX) {
        currX = nextX;
        --nextX;
        continue;
      }
      G[y][currX-1] = G[y][nextX];
      if(G[y][nextX] != 0)
        ret = true;
      G[y][nextX] = 0;
      currX = nextX;
      --nextX;
    }
  }
  return ret;
}

bool moveL(){
  bool ret = false;
  for(int y=N; y>0; --y){
    int currX = 1;
    int nextX = 2;
    while(nextX <= N){
      if(G[y][currX] == 0){
        while(nextX < N && G[y][nextX] == 0) ++nextX;
        
        if(G[y][nextX] != 0) ret = true;
        G[y][currX] = G[y][nextX];
        G[y][nextX] = 0;
        currX = nextX;
        ++nextX;
        continue;
      }
      while(nextX < N && G[y][nextX] == 0){
        ++nextX;
      }
      if(G[y][currX] == G[y][nextX] && !merged[y][currX] && !merged[y][nextX]){
        G[y][currX] += G[y][nextX];
        G[y][nextX] = 0;
        merged[y][currX] = true;
        currX = nextX;
        ++nextX;
        ret = true;
        continue;
      }
      if(currX+1 == nextX) {
        currX = nextX;
        ++nextX;
        continue;
      }
      G[y][currX+1] = G[y][nextX];
      if(G[y][nextX] != 0)
        ret = true;
      G[y][nextX] = 0;
      currX = nextX;
      ++nextX;
    }
  }
  return ret;
}

bool moveU(){
  bool ret = false;
  for(int x=N; x>0; --x){
    int currY = N;
    int nextY = N-1;
    while(nextY > 0){
      if(G[currY][x] == 0){
        while(nextY > 1 && G[nextY][x] == 0) --nextY;

        if(G[nextY][x] != 0) ret = true;
        G[currY][x] = G[nextY][x];
        G[nextY][x] = 0;
        currY = nextY;
        --nextY;
        continue;
      }

      while(nextY > 1 && G[nextY][x] == 0){
        --nextY;
      }
      if(G[currY][x] == G[nextY][x] && !merged[currY][x] && !merged[nextY][x]){
        G[currY][x] += G[nextY][x];
        G[nextY][x] = 0;
        merged[currY][x] = true;
        currY = nextY;
        --nextY;
        ret = true;
        continue;
      }
      if(currY-1 == nextY) {
        currY = nextY;
        --nextY;
        continue;
      }
      G[currY-1][x] = G[nextY][x];
      if(G[nextY][x] != 0)
        ret = true;
      G[nextY][x] = 0;
      currY = nextY;
      --nextY;
    }
  }
  return ret;
}

bool moveD(){
  bool ret = false;
  for(int x=N; x>0; --x){
    int currY = 1;
    int nextY = 2;
    while(nextY <= N){
      if(G[currY][x] == 0){
        while(nextY < N && G[nextY][x] == 0) ++nextY;
        
        if(G[nextY][x] != 0) ret = true;
        G[currY][x] = G[nextY][x];
        G[nextY][x] = 0;
        currY = nextY;
        ++nextY;
        continue;
      }
      while(nextY < N && G[nextY][x] == 0){
        ++nextY;
      }
      if(G[currY][x] == G[nextY][x] && !merged[currY][x] && !merged[nextY][x]){
        G[currY][x] += G[nextY][x];
        G[nextY][x] = 0;
        merged[currY][x] = true;
        currY = nextY;
        ++nextY;
        ret = true;
        continue;
      }
      if(currY+1 == nextY) {
        currY = nextY;
        ++nextY;
        continue;
      }
      G[currY+1][x] = G[nextY][x];
      if(G[nextY][x] != 0)
        ret = true;
      G[nextY][x] = 0;
      currY = nextY;
      ++nextY;
    }
  }
  return ret;
}

void makeComb(vector<char> picked, int idx){
  if(picked.size() == 5){
    v.push_back(picked);
    return;
  }
  if(idx >= 5) return;
  for(int i=0; i<4; ++i){
    picked.push_back(alp[i]);
    makeComb(picked, idx+1);
    picked.pop_back();
    makeComb(picked, idx+1);
  }
}

ull findMax(){
  ull ret = 0;
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      ret = max(ret, G[y][x]);
    }
  }
  return ret;
}

void printG(){
  cout << "\n=============\n";
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      cout << G[y][x] << " ";
      if(G[y][x] <= 9999) cout << " ";
      if(G[y][x] <= 999) cout << " ";
      if(G[y][x] <= 99) cout << " ";
      if(G[y][x] <= 9) cout << " ";
    }cout << "\n";
  }
  cout << "==========\n";
}

void printM(){
  cout << "\n=============\n";
  for(int y=N; y>0; --y){
    for(int x=1; x<=N; ++x){
      cout << merged[y][x] << " ";
    }cout << "\n";
  }
  cout << "==========\n";
}

void solve(){
  getInputs();
  vector<char> temp;
  makeComb(temp, 0);
  ull ans = 0;
  for(auto ways: v){
    backUps();
    // printG();
    // cout << "start\n";
    for(auto way: ways){
      initMerged();
      // cout << way;
      if(way == 'L') while(moveL()){};
      if(way == 'R') while(moveR()){};
      if(way == 'U') while(moveU()){};
      if(way == 'D') while(moveD()){};
      // printG();
    }
    ans = max(ans, findMax());
  }

  cout << ans << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}