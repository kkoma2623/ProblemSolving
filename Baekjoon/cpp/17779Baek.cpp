#include <iostream>

#define MAX_N 20

using namespace std;

int A[MAX_N+1][MAX_N+1];
int N;
int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

void getInput(){
  cin >> N;
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      cin >> A[r][c];
    }
  }
}

bool checkInBound(int x, int y, int d1, int d2){
  
}

int boundary(int a[][MAX_N+1], int _x, int _y, int d1, int d2){
  cout << "x, y => " << _x << ", " << _y << " d1 d2 => " << d1 << " , " << d2 << "\n";
  int people = 0;
  bool visit[N+1][N+1];
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      visit[i][j] = false;
    }
  }
  
  // boundary 1
  for(int i = 0; i <= d1; ++i){
    int r = _x + i;
    int c = _y - i;
    a[r][c] = 5;
    if(!visit[r][c]){
      people += A[r][c];
      visit[r][c] = true;
    }
  }

  // boundary 2
  for(int i = 0; i <= d2; ++i){
    int r = _x + i;
    int c = _y + i;
    a[r][c] = 5;
    if(!visit[_x+i][c]){
      people += A[r][c];
      visit[r][c] = true;
    }
  }

  // boundary 3
  for(int i = d1, j = 0; i <= d1 + d2 && j <= d2; ++i, ++j){
    int r = _x + i;
    int c = _y - d1 + j;
    a[r][c] = 5;
    if(!visit[_x+i][c]){
      people += A[r][c];
      visit[r][c] = true;
    }
  }

  // boundary 4
  for(int i = d2, j = 0; i <= d1 + d2 && j <= d2; ++i, ++j){
    int r = _x + i;
    int c = _y + d2 - j;
    a[r][c] = 5;
    if(!visit[r][c]){
      people += A[r][c];
      visit[r][c] = true;
    }
  }

  cout << "\n====\n";
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cout << a[i][j] << " ";
    }cout << "\n";
  }
  return people;
}

int colorArea(int r, int c, int val, bool visit[][MAX_N+1], int a[][MAX_N+1]){
  if(visit[r][c]){
    return 0;
  }
  visit[r][c] = true;

  for(int i=0; i<4; ++i){
    int nr = r + dir[i][0];
    int nc = c + dir[i][1];
    if(nr < 1 || nc < 1 || nr > MAX_N || nc > MAX_N){
      continue;
    }
    if(a[r][c] == 5){
      continue;
    }

    val += colorArea(nr, nc, val, visit, a);
  }

  return val;
}

void solution(){
  getInput();

  for(int x=1; x<=N; ++x){
    for(int y=1; y<=N; ++y){
      for(int d1 = 1; d1 + x <= N; ++d1){
        for(int d2 = 1; y + d2 <= N; ++d2){
          int _a[MAX_N+1][MAX_N+1];
          for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
              _a[i][j] = 0;
            }
          }
          int area[6];
          area[5] = boundary(_a, x, y, d1, d2);
          bool visit[MAX_N+1][MAX_N+1];
          area[5] += colorArea(x+1, y, A[x+1][y], visit, _a);
          cout << "area " << area[5] << "\n";
        }
      }
    }
  }
  // 기준점 고르고
  // d1 d2 고르고
  // 기준점과 d1 d2로 경계 칠하고
  // 기준점 아래칸부터 5구역 칠하고
  // 1번 선거구 칠하고 몇명인지
  // 2번 선거구 칠하고 몇명인지
  // 3번
  // 4번
  // min max 구하고
  // 차이의 min을 변수에 저장
  // x + d1 + d2 <= N && 1 <= y - d1 && y + d2 <= N 까지
}

int main(){
  // ios::sync_with_stdio(false);
  // cin.tie(0);
  solution();

  return 0;
}