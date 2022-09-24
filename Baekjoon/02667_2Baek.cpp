#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 25

using namespace std;

int N;
int roomN = 1;
int G[MAX_N+1][MAX_N+1];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool visited[MAX_N+1][MAX_N+1];
vector<int> rooms;

void getInputs(){
  cin >> N;
  string temp;
  for(int i=0; i<N; ++i){
    cin >> temp;
    for(int c=0; c<temp.size(); ++c){
      G[i][c] = temp[c]-'0';
    }
  }
}

bool isOutOfBound(int r, int c){
  return r<0 || c<0 || r>=N || c>=N;
}

int dfs(int &currR, int &currC, int cnt){
  if(visited[currR][currC]) return 0;
  visited[currR][currC] = true;
  G[currR][currC] = roomN;

  int ret = cnt;
  for(int i=0; i<4; ++i){
    int nextR = currR + dir[i][0], nextC = currC + dir[i][1];
    if(isOutOfBound(nextR, nextC)) continue;
    if(G[nextR][nextC] == 0) continue;
    if(visited[nextR][nextC]) continue;
    ret += dfs(nextR, nextC, cnt);
  }

  return ret;
}

void printG(){
  for(int r=0; r<N; ++r){
    for(int c=0; c<N; ++c){
      cout << G[r][c] << " ";
    }
    cout << "\n";
  }
}

void solve(){
  getInputs();
  for(int r=0; r<N; ++r){
    for(int c=0; c<N; ++c){
      if(visited[r][c]) continue;
      if(G[r][c] == 0) continue;
      int roomSize = dfs(r, c, 1);
      ++roomN;
      rooms.push_back(roomSize);
    }
  }
  sort(rooms.begin(), rooms.end());
  // printG();
  // cout << "\n";
  cout << rooms.size() << "\n";
  for(auto room : rooms)
    cout << room << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}