#include <iostream>
#include <queue>

#define MAX_SIZE 1001

using namespace std;
struct visitQ{
  int x, y;
  int cnt;
  bool broke;
};


int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool normalVisited[MAX_SIZE][MAX_SIZE];
bool brokenVisited[MAX_SIZE][MAX_SIZE];
int map[MAX_SIZE][MAX_SIZE];
int M, N;
queue<visitQ> q;

int bfs(){
  while(!q.empty()){
    visitQ curr = q.front(); q.pop();
    if(!curr.broke && normalVisited[curr.x][curr.y]) continue;
    if(curr.broke && brokenVisited[curr.x][curr.y]) continue;
    if(curr.x + 1 == M && curr.y + 1 == N) return curr.cnt;
    if(!curr.broke) normalVisited[curr.x][curr.y] = true;
    if(curr.broke) brokenVisited[curr.x][curr.y] = true;

    for(int i=0; i<4; ++i){
      visitQ next = {curr.x + dir[i][0], curr.y + dir[i][1], curr.cnt + 1, curr.broke};
      if(next.x < 0 || next.y < 0 || next.x >= M || next.y >= N) continue;
      if(map[next.x][next.y] == 1 && next.broke) continue;
      if(map[next.x][next.y] == 1) next.broke = true;
      q.push(next);
    }
  }

  return -1;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> M >> N;
  for(int i=0; i<M; ++i){
    string temp; cin >> temp;
    for(int j=0; j<temp.size(); ++j){
      map[i][j] = temp[j] - '0';
    }
  }
  visitQ first = {0, 0, 1, false};
  q.push(first);

  cout << bfs() << "\n";

  return 0;
}