#include <iostream>
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

void moveFireballs(vector<info> (*v)[MAX_N], vector<info> (*nextV)[MAX_N]){
  vector<info> temp[MAX_N][MAX_N];
  // v1 || v2 -> temp
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      if(v[i][j].empty()) continue;

      for(int k=0; k<v[i][j].size(); ++k){
        info t = v[i][j][k];
        int nr = i + d[t.d][0]*v[i][j][k].s, nc = j + d[t.d][1]*v[i][j][k].s;
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

  // temp -> v2 || v1
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      nextV[i][j].swap(temp[i][j]);
    }
  }
}

void mergeFireballs(vector<info> (*v)[MAX_N]){
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      if(v[r][c].size() <= 1) continue;

      int m=0, s=0, d=0;
      int balls = v[r][c].size();
      bool dirEven = v[r][c][0].d % 2 == 0;
      bool dirSame = true;
      // merge balls
      for(int i=0; i<balls; ++i){
        m += v[r][c][i].m;
        s += v[r][c][i].s;
        if(dirEven != v[r][c][i].d % 2 == 0){
          // check dir
          dirSame = false;
        }
      }

      m /= 5;
      if(m == 0){
        // remove fireballs
        vector<info> temp;
        v[r][c].swap(temp);
        continue;
      }

      s /= balls;
      vector<info> temp;
      for(int i=0; i<4; ++i){
        // seperate balls
        temp.push_back({m, s, dirSame ? i*2 : i*2+1});
      }

      // update v[r][c]
      v[r][c].swap(temp);
    }
  }
}

int countFireballs(vector<info> (*v)[MAX_N]){
  int cnt = 0;
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      if(v[r][c].size() == 0){
        continue;
      }

      for(int i=0; i<v[r][c].size(); ++i){
        cnt += v[r][c][i].m;
      }
    }
  }

  return cnt;
}

int solve(){
  getInput();

  for(int i=0; i<K; ++i){
    moveFireballs(i % 2 == 0 ? v1 : v2, i % 2 == 0 ? v2 : v1);
    mergeFireballs(i % 2 == 0 ? v2 : v1);
  }

  return countFireballs(K % 2 == 0 ? v1 : v2);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout << solve();
  return 0;
}