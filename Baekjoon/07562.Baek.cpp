#include <iostream>
#include <vector>
#include <queue>

#define MAX_CELL 301

using namespace std;

int knightWay[8][2] = {{1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}};
struct visitQ
{
  int x, y;
  int cnt;
};

queue<visitQ> visitQue;
int cellSize;
bool visited[MAX_CELL][MAX_CELL];
pair<int, int> dest;

void clearQueue(){
  queue<visitQ> empty;
  swap(visitQue, empty);
}

void clearVisited(){
  for(int i=0; i<MAX_CELL; ++i)
    for(int j=0; j<MAX_CELL; ++j)
      visited[i][j] = false;
}

int bfs(){
  while(!visitQue.empty()){
    visitQ curr = visitQue.front();
    visitQue.pop();

    if(visited[curr.x][curr.y]) continue;

    pair<int, int> currPos = {curr.x, curr.y};
    visited[curr.x][curr.y] = true;
    if(currPos == dest) return curr.cnt;

    for(int i=0; i<8; ++i){
      pair<int, int> toGo = {curr.x + knightWay[i][0], curr.y + knightWay[i][1]};
      if(toGo.first < 0 || toGo.second < 0 || toGo.first >= cellSize || toGo.second >= cellSize) continue;
      if(visited[toGo.first][toGo.second]) continue;
      visitQue.push({toGo.first, toGo.second, curr.cnt + 1});
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int testCases;
  cin >> testCases;
  for(int t=0; t<testCases; ++t){
    cin >> cellSize;
    int posX, posY; cin >> posX >> posY;
    cin >> dest.first >> dest.second;
    clearQueue();
    clearVisited();
    visitQue.push({posX, posY, 0});
    cout << bfs() << '\n';
  }

  return 0;
}