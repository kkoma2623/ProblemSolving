#include <iostream>
#include <queue>

#define MAX_N 21

using namespace std;

struct pos{
  int r, c;

  bool operator<(const pos& p)const{
    if(r == p.r){
      return c < p.c;
    }
    
    return r < p.r;
  }
  bool operator>(const pos& p)const{
    if(r == p.r){
      return c > p.c;
    }
    
    return r > p.r;
  }
};

struct strt{
  int dist;
  pos p;
  pos d;
  int pNum;

  bool operator<(const strt& st)const{
    if(dist == st.dist){
      return p < st.p;
    }

    return dist < st.dist;
  }
  bool operator>(const strt& st)const{
    if(dist == st.dist){
      return p > st.p;
    }

    return dist > st.dist;
  }
};

int nSize, passengerSize;
long long fuel;
int map[MAX_N][MAX_N];
pos taxi;
pos start[MAX_N*MAX_N];
pos dest[MAX_N*MAX_N];
int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void getInput(){
  cin >> nSize >> passengerSize >> fuel;
  for(int r=1; r<=nSize; ++r){
    for(int c=1; c<=nSize; ++c){
      cin >> map[r][c];
    }
  }

  cin >> taxi.r >> taxi.c;

  for(int m=0; m<passengerSize; ++m){
    cin >> start[m].r >> start[m].c >> dest[m].r >> dest[m].c;
  }
}

queue<pair<int, pos>> distMap(int r, int c, int _map[][MAX_N]){
  _map[r][c] = 0;
  
  queue<pair<int, pos>> q;
  q.push({0, {r, c}});

  while(!q.empty()){
    pos nv = q.front().second;
    int dist = q.front().first + 1; q.pop();

    for(int d=0; d<4; ++d){
      int nr = nv.r + dir[d][0], nc = nv.c + dir[d][1];
      if(nr < 1 || nc < 1 || nr > nSize || nc > nSize){
        // out of bound
        continue;
      }
      if(map[nr][nc] == 1){
        // wall
        continue;
      }
      if(_map[nr][nc] != 0){
        // visited
        continue;
      }
      if(nr == r && nc == c){
        // taxi position
        continue;
      }

      _map[nr][nc] = dist;
      q.push({dist, {nr, nc}});
    }
  }

  return q;
}

void initDistMap(int _map[][MAX_N]){
  for(int i=1; i<=nSize; ++i){
    for(int j=1; j<=nSize; ++j){
      if(map[i][j] == 1){
        _map[i][j] = 987654321;
        continue;
      }
      _map[i][j] = map[i][j];
    }
  }
}

void distMapWall(int r, int c, int _map[][MAX_N]){
  for(int i=1; i<=nSize; ++i){
    for(int j=1; j<=nSize; ++j){
      if(i == r && j == c){
        continue;
      }
      if(_map[i][j] == 0){
        _map[i][j] = 987654321;
      }
    }
  }
}

strt findShortestPassenger(int r, int c){
  int _map[MAX_N][MAX_N];
  initDistMap(_map);
  queue<pair<int, pos>> q = distMap(r, c, _map);
  distMapWall(r, c, _map);

  priority_queue<strt, vector<strt>, greater<strt>> pq;
  for(int i=0; i<passengerSize; ++i){
    pos passenger = start[i];
    pos destination = dest[i];
    if(passenger.r < 1 || passenger.c < 1 || passenger.r > nSize || passenger.c > nSize){
      continue;
    }
    pq.push({_map[passenger.r][passenger.c], {passenger.r, passenger.c}, {destination.r, destination.c}, i});
  }

  return pq.top();
}

bool checkCanGo(strt nP){
  return nP.dist <= fuel;
}

int destinationDist(strt passenger){
  int _map[MAX_N][MAX_N];
  initDistMap(_map);

  int r = passenger.p.r, c = passenger.p.c;
  distMap(r, c, _map);
  distMapWall(r, c, _map);

  return _map[passenger.d.r][passenger.d.c];
}

void taxiMove(strt nP){
  int pNum = nP.pNum;
  start[pNum].r = -1;
  start[pNum].c = -1;
  dest[pNum].r = -1;
  dest[pNum].c = -1;
  taxi.r = nP.d.r;
  taxi.c = nP.d.c;
}

void solve(){
  getInput();

  for(int i=0; i<passengerSize; ++i){
    strt nP = findShortestPassenger(taxi.r, taxi.c);
    // check can go
    bool canGo = checkCanGo(nP);
    if(!canGo){
      // can't go
      cout << -1;
      return;
    }
    fuel -= nP.dist;
    //check can go to destination
    int usedFuel = destinationDist(nP);
    if(usedFuel > fuel){
      // can't go
      cout << -1;
      return;
    }

    // can take and go
    fuel += usedFuel;
    taxiMove(nP);
  }

  cout << fuel;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}