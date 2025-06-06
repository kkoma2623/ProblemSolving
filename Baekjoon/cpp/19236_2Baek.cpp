#include <iostream>

#define MAX_N 4

using namespace std;

struct strt{
  int num;
  int r, c;
  int dir;
};

int dir[9][2] = {{0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
strt fish[18];
int tank[MAX_N][MAX_N];

void getInput(){
  fish[0] = {0, -1, -1, -1};
  for(int r=0; r<MAX_N; ++r){
    for(int c=0; c<MAX_N; ++c){
      int num, dir; cin >> num >> dir;
      fish[num] = {num, r, c, dir};
      tank[r][c] = num;
    }
  }
}

int fishDir(strt fish){
  for(int i=0; i<8; ++i){
    int currDir = i + fish.dir;
    if(currDir > 8){
      currDir -= 8;
    }

    int nr = fish.r + dir[currDir][0], nc = fish.c + dir[currDir][1];
    if(nr < 0 || nc < 0 || nr >= MAX_N || nc >= MAX_N){
      // out of bound
      continue;
    }

    if(tank[nr][nc] == 17){
      // shark
      continue;
    }

    return currDir;
  }

  // cannot move
  return -1;
}

void swapFish(strt _fish, int _r, int _c){
  int otherFishNum = tank[_r][_c];
  if(otherFishNum != 0){
    fish[otherFishNum].r = _fish.r;
    fish[otherFishNum].c = _fish.c;
    tank[_r][_c] = _fish.num;

    tank[_fish.r][_fish.c] = otherFishNum;
    fish[_fish.num].r = _r;
    fish[_fish.num].c = _c;
  } else{
    tank[_r][_c] = _fish.num;
    tank[_fish.r][_fish.c] = 0;
    fish[_fish.num].r = _r;
    fish[_fish.num].c = _c;
  }

}

void moveFish(){
  for(int i=1; i<=16; ++i){
    strt currFish = fish[i];
    if(currFish.num == 0){
      // died
      continue;
    }
    
    int _fishDir = fishDir(currFish);
    if(_fishDir == -1){
      // cannot move
      continue;
    }
    currFish.dir = _fishDir;
    fish[i].dir = _fishDir;

    int nr = currFish.r + dir[_fishDir][0], nc = currFish.c + dir[_fishDir][1];
    if(nr < 0 || nc < 0 || nr >= MAX_N || nc >= MAX_N){
      continue;
    }

    swapFish(fish[i], nr, nc);
  }
}

int moveShark(int r, int c, int _dir, int dist){
  int nr = r + dir[_dir][0]*dist, nc = c + dir[_dir][1]*dist;
  if(nr < 0 || nc < 0 || nr >= MAX_N || nc >= MAX_N){
    // out of bound
    return -987654321;
  }
  if(tank[nr][nc] == 0){
    // no fish
    return -987654321;
  }

  // eat
  int eatenFish = tank[nr][nc];
  tank[nr][nc] = 17;
  fish[17].r = nr;
  fish[17].c = nc;
  fish[17].dir = fish[eatenFish].dir;
  fish[eatenFish].num = 0;
  tank[r][c] = 0;

  return eatenFish;
}

// dfs after shark ate (0, 0)
int dfs(int _r, int _c, int val){
  if(_r < 0 || _c < 0 || _r >= MAX_N || _c >= MAX_N){
    // out of bound
    return val;
  }

  moveFish();

  // save
  int _tank[MAX_N][MAX_N];
  for(int r=0; r<MAX_N; ++r){
    for(int c=0; c<MAX_N; ++c){
      _tank[r][c] = tank[r][c];
    }
  }
  strt _fish[18];
  for(int i=1; i<=17; ++i){
    _fish[i] = fish[i];
  }

  int ret = val;

  for(int dist=1; dist<=3; ++dist){
    strt shark = fish[17];
    int nr = shark.r + dir[shark.dir][0]*dist, nc = shark.c + dir[shark.dir][1]*dist;
    if(nr < 0 || nc < 0 || nr >= MAX_N || nc >= MAX_N){
      // out of bound
      continue;
    }
    if(tank[nr][nc] == 0){
      // no fish to eat
      continue;
    }

    // eat fish
    int score = moveShark(shark.r, shark.c, shark.dir, dist);
    // dfs, choose max val from dist 1, 2, 3
    ret = max(ret, dfs(nr, nc, val + score));

    // recovery tank and fish
    for(int r=0; r<MAX_N; ++r){
      for(int c=0; c<MAX_N; ++c){
        tank[r][c] = _tank[r][c];
      }
    }
    for(int i=1; i<=17; ++i){
      fish[i] = _fish[i];
    }
  }

  return ret;
}


int solve(){
  getInput();
  int val = tank[0][0];
  fish[val].num = 0;
  tank[0][0] = 17;

  fish[17].r = 0;
  fish[17].c = 0;
  fish[17].num = 17;
  fish[17].dir = fish[val].dir;

  val = dfs(0, 0, val);

  return val;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cout << solve();

  return 0;
}