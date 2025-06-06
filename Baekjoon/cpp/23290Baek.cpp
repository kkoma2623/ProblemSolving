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
struct fish{
  int y, x;
  int d;
};
queue<fish> fishQ;
queue<fish> copiedFishQ;
int sharkY, sharkX;
int fishG[MAX_N+1][MAX_N+1];
int fishSmellMap[MAX_N+1][MAX_N+1];
vector<vector<int>> sharkDirVec;
bool visitedShark[MAX_N+1][MAX_N+1];

void printFishG(queue<fish> tempQ){
  while(!tempQ.empty()){
    cout << tempQ.front().y << ", " << tempQ.front().x << ": ";
    cout << tempQ.front().d << "\n";
    tempQ.pop();
  }cout << "\n";
}

void getInputs(){
  cin >> M >> S;
  for(int i=0; i<M; ++i){
    fish f;
    cin >> f.y >> f.x >> f.d;
    fishQ.push(f);
  }
  cin >> sharkY >> sharkX;
}

bool isOutOfBound(int y, int x){
  return y < 1 || x < 1 || y > MAX_N || x > MAX_N;
}

void initSharkDirVec(int idx, vector<int> selected){
  if(selected.size() >= 3){
    sharkDirVec.push_back(selected);
    return;
  }
  
  for(int i=1; i<=4; ++i){
    selected.push_back(i);
    initSharkDirVec(idx, selected);
    selected.pop_back();
  }
}

void copyFishes(queue<fish> fQ){
  while(!copiedFishQ.empty()) copiedFishQ.pop();

  while(!fQ.empty()){
    copiedFishQ.push(fQ.front());
    fQ.pop();
  }
}

void moveFishes(){
  queue<fish> movedFishes;
  while(!fishQ.empty()){
    fish curr = fishQ.front();
    fishQ.pop();
    for(int i=0; i<8; ++i){
      int nDir = (curr.d - i);
      if(nDir < 1) nDir += 8;
      int ny = curr.y + fishDir[nDir][0], nx = curr.x + fishDir[nDir][1];
      if(isOutOfBound(ny, nx)) continue;
      if(sharkY == ny && sharkX == nx) continue;
      if(fishSmellMap[ny][nx] > 0) continue;
      curr.y = ny; curr.x = nx;
      curr.d = nDir;
      break;
    }
    movedFishes.push(curr);
  }

  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      fishG[y][x] = 0;
    }
  }
  while(!movedFishes.empty()){
    fish curr = movedFishes.front(); movedFishes.pop();
    fishQ.push(curr);
    ++fishG[curr.y][curr.x];
  }
}

pair<int, vector<int>> moveShark(vector<int> &moves, int idx, int cnt){
  if(isOutOfBound(sharkY, sharkX)) return{-1, moves};
  if(visitedShark[sharkY][sharkX]) return{-1, moves};

  if(idx >= 3){
    return {cnt, moves};
  }
  cnt += fishG[sharkY][sharkX];
  visitedShark[sharkY][sharkX] = true;

  int nextSharkY = sharkY + sharkDir[moves[idx]][0], nextSharkX = sharkX + sharkDir[moves[idx]][1];
  if(isOutOfBound(nextSharkY, nextSharkX)) return{-1, moves};
  if(visitedShark[nextSharkY][nextSharkX]) return{-1, moves};
  sharkY = nextSharkY; sharkX = nextSharkX;
  return moveShark(moves, idx+1, cnt);
}

void eatFishes(pair<int, vector<int>> p, int idx){

  if(fishG[sharkY][sharkX]){
    fishG[sharkY][sharkX] = 0;
    fishSmellMap[sharkY][sharkX] = 3;
  }

  if(idx == 3) return;

  int sharkD = p.second[idx];
  // cout << "move " << sharkD << "\n";
  sharkY += sharkDir[sharkD][0];
  sharkX += sharkDir[sharkD][1];
  eatFishes(p, idx+1);
}

void removeSmell(){
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      --fishSmellMap[y][x];
      if(fishSmellMap[y][x] < 0) fishSmellMap[y][x] = 0;
    }
  }
}

void copyEnd(){
  queue<fish> tempQ;
  while(!fishQ.empty()){
    fish curr = fishQ.front(); fishQ.pop();
    if(fishG[curr.y][curr.x] == 0) continue;
    tempQ.push(curr);
  }
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      fishG[y][x] = 0;
    }
  }
  while(!tempQ.empty()){
    fishQ.push(tempQ.front());
    ++fishG[tempQ.front().y][tempQ.front().x];
    tempQ.pop();
  }
  while(!copiedFishQ.empty()){
    fishQ.push(copiedFishQ.front());
    ++fishG[copiedFishQ.front().y][copiedFishQ.front().x];
    copiedFishQ.pop();
  }
}

bool cmp(const pair<int, vector<int>>& a, const pair<int, vector<int>>& b) {
  if(a.first == b.first){
    for(int i=0; i<3; ++i){
      if(a.second[i] < b.second[i]) return a.second[i] < b.second[i];
    }
  }

  return a.first > b.first;
}

void solve(){
  getInputs();
  vector<int> v;
  initSharkDirVec(0, v);
  for(int i=0; i<S; ++i){
    copyFishes(fishQ);
    moveFishes();
    // cout << "movefishes\n";
    // printFishG(fishQ);
    vector<pair<int, vector<int>>> vec;
    int currSharkY = sharkY, currSharkX = sharkX;
    for(auto sdv: sharkDirVec){
      for(int y=1; y<=MAX_N; ++y){
        for(int x=1; x<=MAX_N; ++x){
          visitedShark[y][x] = false;
        }
      }
      int nextSharkY = sharkY + sharkDir[sdv[0]][0], nextSharkX = sharkX + sharkDir[sdv[0]][1];
      sharkY = nextSharkY; sharkX = nextSharkX;
      vec.push_back(moveShark(sdv, 1, 0));
      sharkY = currSharkY; sharkX = currSharkX;
    }
    sort(vec.begin(), vec.end(), cmp);
    eatFishes(vec[0], 0);
    // cout << "after eat\n";
    // printFishG(fishQ);
    // cout << "\n";
    // cout << "shark " << sharkY << ", " << sharkX << "\n";
    removeSmell();
    copyEnd();
    // cout << "end\n";
    // printFishG(fishQ);
  }

  int cnt = 0;
  for(int y=1; y<=MAX_N; ++y){
    for(int x=1; x<=MAX_N; ++x){
      cnt += fishG[y][x];
    }
  }

  cout << cnt << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}