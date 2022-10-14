#include <iostream>

#define MAX_N 50

using namespace std;

string G[MAX_N+1][MAX_N+1];
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int N;

int getMoveDir(int y, int x){
  int con = (N+1);
  if(y == con/2 && x == con/2) return 3;
  if(y-x <= 0 && y+x > con) return 1;
  if(y-x >= 1 && y+x < con) return 2;
  if(y+x <= con && y-x < 1) return 3;
  if(y+x >= con && y-x > 0) return 4;

  return 0;
}

int getMoveDirReverse(int y, int x){
  int con = (N+1);
  if(y == con/2 && x == con/2) return 3;
  if(y-x < 0 && y+x >= con) return 2;
  if(y-x > 1 && y+x <= con) return 1;
  if(y+x < con && y-x <= 1) return 4;
  if(y+x > con && y-x >= 0) return 3;

  return 0;
}

string getString(int i){
  switch(i){
    case 1:
      return "상";
    case 2:
      return "하";
    case 3:
      return "좌";
    case 4:
      return "우";
    default:
      return "ㅁ";
  }
}

void makeG(bool isReverse){
  if(isReverse){
    for(int y=1; y<=N; ++y){
      for(int x=1; x<=N; ++x){
        int moveDir = getMoveDirReverse(y, x);
        G[y][x] = getString(moveDir);
      }
    }
  } else {
    for(int y=1; y<=N; ++y){
      for(int x=1; x<=N; ++x){
        int moveDir = getMoveDir(y, x);
        G[y][x] = getString(moveDir);
      }
    }
  }
}

void printG(){
  int isReverse = false;
  for(int y=1; y<=N; ++y){
    for(int x=1; x<=N; ++x){
      cout << G[y][x] << " ";
    }cout << "\n";
  }


}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> N;
  makeG(false);
  printG();
  makeG(true);
  cout << "\n======\n";
  printG();

  return 0;
}