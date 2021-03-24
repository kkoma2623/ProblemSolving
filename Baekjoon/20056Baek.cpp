#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 51

using namespace std;

class info{
  public:
    int m, s, d;
};

int d[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
vector<info> v1[MAX_N][MAX_N], v2[MAX_N][MAX_N];
int N, M, K;

void getInput(){
  cin >> N >> M >> K;

  for(int i=0; i<M; ++i){
    int r, c;
    info temp; cin >> r >> c >> temp.m >> temp.s >> temp.d;
    v1[r][c].push_back(temp);
  }
}

void moveFireballs(int n){
  if(n%2 == 0){
    // v1 -> v2
    vector<info> temp[MAX_N][MAX_N];

    // v1 -> temp
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=N; ++j){
        if(v1[i][j].empty()) continue;

        for(int v=0; v<v1[i][j].size(); ++v){
          info t = v1[i][j][v];
          int nr = i + d[t.d][0]*v1[i][j][v].s, nc = j + d[t.d][1]*v1[i][j][v].s;
          while(nr > N){
            nr -= N;
          }
          while(nc > N){
            nc -= N;
          }
          while(nr <= 0){
            nr += N;
          }
          while(nc <= 0){
            nc += N;
          }
          temp[nr][nc].push_back(t);
        }
      }
    }

    // temp -> v2
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=N; ++j){
        v2[i][j].swap(temp[i][j]);
      }
    }
  } else{
    // v2 -> v1
    vector<info> temp[MAX_N][MAX_N];

    // v2 -> temp
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=N; ++j){
        if(v2[i][j].empty()) continue;

        for(int v=0; v<v2[i][j].size(); ++v){
          info t = v2[i][j][v];
          int nr = i + d[t.d][0]*v2[i][j][v].s, nc = j + d[t.d][1]*v2[i][j][v].s;
          while(nr > N){
            nr -= N;
          }
          while(nc > N){
            nc -= N;
          }
          while(nr <= 0){
            nr += N;
          }
          while(nc <= 0){
            nc += N;
          }
          temp[nr][nc].push_back(t);
        }
      }
    }

    // temp -> v1
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=N; ++j){
        v1[i][j].swap(temp[i][j]);
      }
    }
  }
}

void mergeFireballs(int n){
  if(n%2 == 0){
    // v2
    for(int r=1; r<=N; ++r){
      for(int c=1; c<=N; ++c){
        if(v2[r][c].size() <= 1) continue;

        int m=0, s=0, d=0;
        int balls = v2[r][c].size();
        bool dirEven = v2[r][c][0].d % 2 == 0;
        bool dirSame = true;
        // merge balls
        for(int i=0; i<balls; ++i){
          m += v2[r][c][i].m;
          s += v2[r][c][i].s;
          if(dirEven != v2[r][c][i].d % 2 == 0){
            // check dir
            dirSame = false;
          }
        }

        m /= 5;
        if(m == 0){
          // remove fireballs
          vector<info> temp;
          v2[r][c].swap(temp);
          continue;
        }

        s /= balls;
        vector<info> temp;
        for(int i=0; i<4; ++i){
          // seperate balls
          temp.push_back({m, s, dirSame ? i*2 : i*2+1});
        }

        // update v2[r][c]
        v2[r][c].swap(temp);
      }
    }
  } else{
    // v1
    for(int r=1; r<=N; ++r){
      for(int c=1; c<=N; ++c){
        if(v1[r][c].size() <= 1) continue;

        int m=0, s=0, d=0;
        int balls = v1[r][c].size();
        bool dirEven = v1[r][c][0].d % 2 == 0;
        bool dirSame = true;
        // merge balls
        for(int i=0; i<balls; ++i){
          m += v1[r][c][i].m;
          s += v1[r][c][i].s;
          if(dirEven != v1[r][c][i].d % 2 == 0){
            // check dir
            dirSame = false;
          }
        }

        m /= 5;
        if(m == 0){
          // remove fireballs
          vector<info> temp;
          v1[r][c].swap(temp);
          continue;
        }

        s /= balls;
        vector<info> temp;
        for(int i=0; i<4; ++i){
          // seperate balls
          temp.push_back({m, s, dirSame ? i*2 : i*2+1});
        }

        // update v1[r][c]
        v1[r][c].swap(temp);
      }
    }
  }
}

int countFireballs(int n){
  int cnt = 0;
  if(n % 2 != 0){
    // v2
    for(int r=1; r<=N; ++r){
      for(int c=1; c<=N; ++c){
        if(v2[r][c].size() == 0){
          continue;
        }

        for(int i=0; i<v2[r][c].size(); ++i){
          cnt += v2[r][c][i].m;
        }
      }
    }
  } else{
    // v1
    for(int r=1; r<=N; ++r){
      for(int c=1; c<=N; ++c){
        if(v1[r][c].size() == 0){
          continue;
        }

        for(int i=0; i<v1[r][c].size(); ++i){
          cnt += v1[r][c][i].m;
        }
      }
    }
  }

  return cnt;
}

int solve(){
  getInput();

  for(int i=0; i<K; ++i){
    moveFireballs(i);
    mergeFireballs(i);
  }

  return countFireballs(K);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << solve();
  return 0;
}