#include <iostream>
#include <vector>

#define MAX_N 50

using namespace std;

struct pos{
  int r, c;
};


int N, L, R;
int nation[MAX_N+1][MAX_N+1];
int unionedMap[MAX_N+1][MAX_N+1];
int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void getInput(){
  cin >> N >> L >> R;
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cin >> nation[i][j];
    }
  }
}

bool boundCheck(int r, int c){
  return r < 1 || c < 1 || r > N || c > N;
}

vector<pos> unionNationVector(int _r, int _c, bool visited[][MAX_N+1]){
  vector<pos> v;
  if(boundCheck(_r, _c)){
    return v;
  }
  if(visited[_r][_c]){
    return v;
  }
  visited[_r][_c] = true;
  
  const int currPeople = nation[_r][_c];

  for(int i=0; i<4; ++i){
    int nr = _r + dir[i][0];
    int nc = _c + dir[i][1];
    if(boundCheck(nr, nc)){
      // out of bound
      continue;
    }
    if(visited[nr][nc]){
      // visited
      continue;
    }
    const int nextPeople = nation[nr][nc];
    const int diffPoeple = abs(currPeople - nextPeople);
    if(diffPoeple < L || R < diffPoeple){
      // not in range
      continue;
    }
    v.push_back({nr, nc});
    vector<pos> dfsV = unionNationVector(nr, nc, visited);
    v.insert(v.end(), dfsV.begin(), dfsV.end());
  }

  return v;
}

void initVisit(bool visit[][MAX_N+1]){
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      visit[i][j] = false;
    }
  }
}

void initUnionedMap(){
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      unionedMap[r][c] = nation[r][c];
    }
  }
}

int syncMap(){
  int diffCnt = 0;
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      if(nation[r][c] == unionedMap[r][c]){
        continue;
      }
      nation[r][c] = unionedMap[r][c];
      ++diffCnt;
    }
  }

  return diffCnt;
}

void unionAtUnionedMap(vector<pos> v){
  int cellCnt = v.size();
  int peopleSum = 0;
  for(auto &it : v){
    peopleSum += nation[it.r][it.c];
  }
  int peopleCell = peopleSum/cellCnt;

  for(auto &it : v){
    unionedMap[it.r][it.c] = peopleCell;
  }
}

void solve(){
  getInput();
  int cnt = 0;
  while(true){
    // start
    bool visit[MAX_N+1][MAX_N+1];
    initVisit(visit);
    initUnionedMap();
    
    for(int r=1; r<=N; ++r){
      for(int c=1; c<=N; ++c){
        vector<pos> v = unionNationVector(r, c, visit);
        if(v.empty()){
          // no union
          continue;
        }
        v.push_back({r, c}); // push back current territory
        unionAtUnionedMap(v);
      }
    }
    int diffCnt = syncMap();
    if(diffCnt == 0){
      cout << cnt;
      return;
    }
    //end
    ++cnt;
  }

}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}