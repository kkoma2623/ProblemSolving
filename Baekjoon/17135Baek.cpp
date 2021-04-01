#include <iostream>
#include <queue>

#define MAX_N 15

using namespace std;

struct strt{
  int r, c;
  int dist;
};


int N, M, D;
int ene[MAX_N+1][MAX_N+1];
int dir[3][2] = {{0, -1}, {-1, 0}, {0, 1}};

void getInput(){
  cin >> N >> M >> D;
  for(int r=0; r<N; ++r){
    for(int c=0; c<M; ++c){
      cin >> ene[r][c];
    }
  }
}

bool checkCanShoot(int r, int c, int bowC){
  return abs(r - N) + abs(c - bowC) <= D;
}

bool checkBoundary(int r, int c){
  return (r < 0 || c < 0 || r >= N || c >= M);
}

strt findShortest(int c){
  queue<strt> q;
  q.push({N-1, c, 1}); // push archer front
  bool visited[N+1][M+1];
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      visited[i][j] = false;
    }
  }

  while(!q.empty()){
    strt curr = q.front(); q.pop();
    if(visited[curr.r][curr.c]){
      continue;
    }
    visited[curr.r][curr.c] = true;

    if(!checkCanShoot(curr.r, curr.c, c)){
      // can't shoot

      return {0, 0, 0};
    }
    if(ene[curr.r][curr.c] != 0){
      // find shortest
      return curr;
    }

    for(int i=0; i<3; ++i){
      int nr = curr.r + dir[i][0];
      int nc = curr.c + dir[i][1];
      if(checkBoundary(nr, nc)){
        continue;
      }
      q.push({nr, nc, curr.dist + 1});
    }
  }

  return {0, 0, 0};
}

// c1 < c2 < c3
int shoot(int c1, int c2, int c3){
  int kill = 0;

  strt c1Kill = findShortest(c1);
  strt c2Kill = findShortest(c2);
  strt c3Kill = findShortest(c3);

  if(c1Kill.dist != 0){
    if(ene[c1Kill.r][c1Kill.c]){
      ene[c1Kill.r][c1Kill.c] = 0;
      ++kill;
    }
  }
  if(c2Kill.dist != 0){
    if(ene[c2Kill.r][c2Kill.c]){
      ene[c2Kill.r][c2Kill.c] = 0;
      ++kill;
    }
  }
  if(c3Kill.dist != 0){
    if(ene[c3Kill.r][c3Kill.c]){
      ene[c3Kill.r][c3Kill.c] = 0;
      ++kill;
    }
  }

  return kill;
}

void moveEnemy(){
  for(int c=0; c<M; ++c){
    ene[N-1][c] = 0;
  }

  for(int r=N-1; r>0; --r){
    for(int c=0; c<M; ++c){
      ene[r][c] = ene[r-1][c];
    }
  }
  for(int c=0; c<M; ++c){
    ene[0][c] = 0;
  }
}

void copyEne(int _ene[][MAX_N+1]){
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      _ene[i][j] = ene[i][j];
    }
  }
}

void restoreEne(int _ene[][MAX_N+1]){
  for(int i=0; i<N; ++i){
    for(int j=0; j<M; ++j){
      ene[i][j] = _ene[i][j];
    }
  }
}

void solve(){
  getInput();
  int score = 0;
  for(int c1=0; c1<M-2; ++c1){
    for(int c2=c1+1; c2<M-1; ++c2){
      for(int c3=c2+1; c3<M; ++c3){
        int kill = 0;
        int n = N;
        int _ene[MAX_N+1][MAX_N+1];
        copyEne(_ene);

        while(n--){
          kill += shoot(c1, c2, c3);
          moveEnemy();
        }
        score = max(score, kill);
        restoreEne(_ene);
      }
    }
  }

  cout << score;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}