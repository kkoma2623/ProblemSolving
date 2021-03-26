#include <iostream>

#define MAX_N 500
#define PIVOT 2

using namespace std;


int tDir[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int map[MAX_N][MAX_N];
int tRatio[5][5];
int N;
int tPivot;

void getInput(){
  cin >> N;
  tPivot = N/2 + 1;
  for(int r=1; r<=N; ++r){
    for(int c=1; c<=N; ++c){
      int temp; cin >> temp;
      map[r][c] = temp;
    }
  }
}

void setTRatio(){
  tRatio[PIVOT-2][PIVOT] = 2;
  tRatio[PIVOT+2][PIVOT] = 2;
  tRatio[PIVOT-1][PIVOT+1] = 1;
  tRatio[PIVOT+1][PIVOT+1] = 1;
  tRatio[PIVOT-1][PIVOT] = 7;
  tRatio[PIVOT+1][PIVOT] = 7;
  tRatio[PIVOT-1][PIVOT-1] = 10;
  tRatio[PIVOT+1][PIVOT-1] = 10;
  tRatio[PIVOT][PIVOT-2] = 5;
  tRatio[PIVOT][PIVOT-1] = -1;
}

int moveTornado(int r, int c){
  int outSand = 0;
  int movedSand = 0;
  int currSand = map[r][c];
  int temp[5][5];
  pair<int, int> other;
  for(int i=0; i<5; ++i){
    for(int j=0; j<5; ++j){
      if(tRatio[i][j] == -1){
        other = {i, j};
        continue;
      }
      temp[i][j] = (tRatio[i][j]*currSand)/100;
      movedSand += (tRatio[i][j]*currSand)/100;
    }
  }
  temp[other.first][other.second] = currSand - movedSand;

  for(int i=0; i<5; ++i){
    for(int j=0; j<5; ++j){
      int tempR = r + i-PIVOT, tempC = c + j-PIVOT;
      if(tempR < 1 || tempC < 1 || tempR > N || tempC > N){
        outSand += temp[i][j];
        continue;
      }
      map[tempR][tempC] += temp[i][j];
    }
  }
  map[r][c] = 0;

  return outSand;
}

void rotateT(){
  int temp[5][5];
  for(int r=0; r<5; ++r){
    for(int c=0; c<5; ++c){
      temp[5-c-1][r] = tRatio[r][c];
    }
  }
  for(int r=0; r<5; ++r){
    for(int c=0; c<5; ++c){
      tRatio[r][c] = temp[r][c];
    }
  }
}

int solution(){
  getInput();
  setTRatio();
  int tDirNum = 0;
  int r = tPivot, c = tPivot - 1; // tornado start position
  int outSand = 0;
  int stop = 0;
  while((r != 1 || c != 1)){
    outSand += moveTornado(r, c);
    if((r - tPivot - 1 == c - tPivot) && (c - tPivot < 0)){
      rotateT();
      ++tDirNum;
    } else if((abs(r - tPivot) == abs(c - tPivot)) && (r - tPivot > 0 || c - tPivot > 0)){
      rotateT();
      ++tDirNum;
    }

    r += tDir[tDirNum%4][0];
    c += tDir[tDirNum%4][1];
  }
  outSand += moveTornado(1, 1);
  
  return outSand;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cout << solution();

  return 0;
}