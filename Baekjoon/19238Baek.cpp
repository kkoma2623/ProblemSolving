#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 20
#define INF 987654321

using namespace std;

int N;
int road[MAX_N+2][MAX_N+2];
int way[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int visited[MAX_N+2][MAX_N+2];

struct customer{
  int number;
  pair<int, int> start;
  pair<int, int> goal;
};

void visitedClear(){
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      if(road[i][j] == 1){
        visited[i][j] = INF;
      }
      else{
        visited[i][j] = 1;
      }
    }
  }
  for(int i=0; i<=N; ++i){
    visited[i][0] = INF;
    visited[0][i] = INF;
    visited[i][N+1] = INF;
    visited[N+1][i] = INF;
  }
}

void bfsFindCloser(pair<int, int> taxi){

  queue<pair<int, int>> q;
  for(int i=0; i<4; ++i){
    if(road[taxi.first+way[i][0]][taxi.second+way[i][1]] != INF && visited[taxi.first+way[i][0]][taxi.second+way[i][1]] != INF
     && taxi.first+way[i][0] > 0 && taxi.first+way[i][0] <= N  && taxi.second+way[i][1] > 0 && taxi.second+way[i][1] <= N){
       q.push({taxi.first+way[i][0], taxi.second+way[i][1]});
       visited[taxi.first+way[i][0]][taxi.second+way[i][1]] = 1;
    }
  }

  while(!q.empty()){
    pair<int, int> start = q.front(); q.pop();
    for(int i=0; i<4; ++i){
      if(road[start.first+way[i][0]][start.second+way[i][1]] != INF && visited[start.first+way[i][0]][start.second+way[i][1]] == 1
      && start.first+way[i][0] > 0 && start.first+way[i][0] <= N  && start.second+way[i][1] > 0 && start.second+way[i][1] <= N){
        q.push({start.first+way[i][0], start.second+way[i][1]});
        visited[start.first+way[i][0]][start.second+way[i][1]] += visited[start.first][start.second];
      }
    }
  }

  for(int i=0; i<4; ++i){
    if(road[taxi.first+way[i][0]][taxi.second+way[i][1]] != INF && visited[taxi.first+way[i][0]][taxi.second+way[i][1]] != INF
     && taxi.first+way[i][0] > 0 && taxi.first+way[i][0] <= N  && taxi.second+way[i][1] > 0 && taxi.second+way[i][1] <= N){
       visited[taxi.first+way[i][0]][taxi.second+way[i][1]] = 1;
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int M, F; cin >> N >> M  >> F;

  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cin >> road[i][j];
      if(road[i][j] == 1){
      }
    }
  }

  pair<int, int> taxi; cin >> taxi.first >> taxi.second;
  vector<customer> c(M);
  
  cout << "\n" << "\n";
  for(int i=0; i<M; ++i){
    cin >> c[i].start.first >> c[i].start.second >> c[i].goal.first >> c[i].goal.second;
    c[i].number = i+1;
  }

  for(int cc=0; cc<M; ++cc){
    // 거리 초기화
    visitedClear();
    visited[taxi.first][taxi.second] = 0;

    // 거리 갱신
    bfsFindCloser(taxi);
    
    // 얼마 걸리나, 누가
    // 거리, 누구
    pair<int, int> son = {visited[c[0].start.first][c[0].start.second], c[0].number};
    cout << son.second << " start\n";
    for(auto iter=c.begin() + 1; iter!=c.end(); ++iter){
      // 더 작은놈 찾음
      if(son.first > visited[(*iter).start.first][(*iter).start.second]){
        cout << "find smaller\n";
        son = {visited[(*iter).start.first][(*iter).start.second], (*iter).number};
      }
      // 같은놈 찾음
      else if(son.first == visited[(*iter).start.first][(*iter).start.second]){
        // 같은놈에 행이 더 작은놈 찾음
        if(c[son.second-1].start.first > c[(*iter).number-1].start.first){
          cout << "row lower\n";
          son = {visited[(*iter).start.first][(*iter).start.second], (*iter).number};
        }
        // 같은놈에 행도 같음
        else if (c[son.second-1].start.first == c[(*iter).number-1].start.first) {
          // 같은놈에 행도 같지만 열이 더 작은놈 찾음
          if (c[son.second-1].start.second > c[(*iter).number-1].start.second){
            son = {visited[(*iter).start.first][(*iter).start.second], (*iter).number};
          }
        }
      }
    }
    cout << son.second << " is \n";

    // 최단거리가 연로 바닥나면 끝냄
    if(son.first > F){
      cout << -1;
      return 0;
    }

    // 연료 빼주고.
    F -= son.first;

    // 목적지 가야지
    // 거리 초기화
    visitedClear();
    // 택시 이동.
    taxi = c[son.second - 1].start;
    // 거리 갱신
    bfsFindCloser(taxi);
    cout << "\n";
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=N; ++j){
        cout << visited[i][j] << " ";
      }
      cout << "\n";
    }
    // 연료 넘으면 -1
    if(visited[c[son.second - 1].goal.first][c[son.second - 1].goal.second] > F){
      cout << -1;
      return 0;
    }
    cout << F << " before Fuel\n";
    // 연료 갱신
    F += visited[c[son.second - 1].goal.first][c[son.second - 1].goal.second];
    cout << F << " charged Fuel\n";
    // 손님 지우기
    c.erase(c.begin() + son.second - 1);

    for(int i=0; i<c.size(); ++i){
      cout << c[i].number << " remain\n";
    }
  }

  cout << F;
  return 0;
}