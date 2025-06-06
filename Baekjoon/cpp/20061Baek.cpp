#include <iostream>

#define MAX_N 10
#define RED_MAX 4
#define GREEN_R 4
#define BLUE_C 4

using namespace std;

int board[MAX_N+1][MAX_N+1];

void moveTypeOne(int _r, int _c){
  int r = _r, c = _c;
  
  // green
  r = GREEN_R + 1;
  board[r][c] = 1;
  while(board[++r][c] != 1){
    if(r >= MAX_N){
      break;
    }
    if(board[r][c] != 0){
      break;
    }
    board[r][c] = 1;
    board[r-1][c] = 0;
  }

  // blue
  r = _r; c = BLUE_C + 1;
  board[r][c] = 1;
  while(board[r][++c] != 1){
    if(c >= MAX_N){
      break;
    }
    if(board[r][c] != 0){
      break;
    }
    board[r][c] = 1;
    board[r][c-1] = 0;
  }
}

void colorTypeTwo(int r, int c1, int c2, int color){
  board[r][c1] = color; board[r][c2] = color;
}

void moveTypeTwo(int _r, int _c){
  int r = _r, c1 = _c, c2 = _c + 1;

  // green
  r = GREEN_R + 1;
  colorTypeTwo(r, c1, c2, 1);
  ++r;
  while(board[r][c1] != 1 && board[r][c2] != 1){
    if(r >= MAX_N){
      break;
    }
    if(board[r][c1] != 0 || board[r][c2] != 0){
      break;
    }
    colorTypeTwo(r, c1, c2, 1);
    colorTypeTwo(r-1, c1, c2, 0);
    ++r;
  }

  // blue
  r = _r; c1 = BLUE_C; c2 = BLUE_C + 1;
  colorTypeTwo(r, c1, c2, 1);
  while(board[r][++c2] != 1){
    if(c2 >= MAX_N){
      break;
    }
    if(board[r][c2] != 0){
      break;
    }
    ++c1;
    colorTypeTwo(r, c1-1, c2-1, 0);
    colorTypeTwo(r, c1, c2, 1);
  }
}

void colorTypeThree(int r1, int r2, int c, int color){
  board[r1][c] = color; board[r2][c] = color;
}

void moveTypeThree(int _r, int _c){
  int r1 = _r, r2 = _r + 1, c = _c;

  // green
  r1 = GREEN_R; r2 = GREEN_R + 1;
  colorTypeThree(r1, r2, c, 1);
  while(board[++r2][c] != 1){
    if(r2 >= MAX_N){
      break;
    }
    if(board[r2][c] != 0){
      break;
    }
    ++r1;
    colorTypeThree(r1-1, r2-1, c, 0);
    colorTypeThree(r1, r2, c, 1);
  }

  // blue
  r1 = _r, r2 = _r + 1, c = BLUE_C + 1;
  colorTypeThree(r1, r2, c, 1);
  ++c;
  while(board[r1][c] != 1 && board[r2][c] != 1){
    if(c >= MAX_N){
      break;
    }
    if(board[r1][c] != 0 || board[r2][c] != 0){
      break;
    }
    colorTypeThree(r1, r2, c, 1);
    colorTypeThree(r1, r2, c-1, 0);
    ++c;
  }
}

int checkRow(int r){
  int ret = 1;

  for(int i=0; i<RED_MAX; ++i){
    if(board[r][i] != 0 && (r == 4 || r == 5)){
      return 2;
    }
    if(board[r][i] == 0){
      ret = 0;
    }
  }

  return ret;
}

int checkCol(int c){
  int ret = 1;

  for(int i=0; i<RED_MAX; ++i){
    if(board[i][c] != 0 && (c == 4 || c == 5)){
      return 2;
    }
    if(board[i][c] == 0){
      ret = 0;
    }
  }

  return ret;
}

void downRow(int _r){
  for(int r = _r; r>=RED_MAX; --r){
    for(int c=0; c<RED_MAX; ++c){
      board[r][c] = board[r-1][c];
    }
  }
}

void rightCol(int _c){
  for(int c = _c; c>=RED_MAX; --c){
    for(int r=0; r<RED_MAX; ++r){
      board[r][c] = board[r][c-1];
    }
  }
}

int removeBlocks(){
  int totalScore = 0;
  // green
  for(int r=MAX_N; r>GREEN_R; --r){
    int tmpScore = checkRow(r);
    if(tmpScore == 0){
      continue;
    }
    if(tmpScore == 2){
      downRow(MAX_N);
      ++r;
      continue;
    }
    totalScore += tmpScore;
    for(int c = 0; c<RED_MAX; ++c){
      board[r][c] = 0;
    }
    downRow(r++);
  }

  // blue
  for(int c=MAX_N; c>BLUE_C; --c){
    int tmpScore = checkCol(c);
    if(tmpScore == 0){
      continue;
    }
    if(tmpScore == 2){
      rightCol(MAX_N);
      ++c;
      continue;
    }
    totalScore += tmpScore;
    for(int r=0; r<RED_MAX; ++r){
      board[r][c] = 0;
    }
    rightCol(c++);
  }

  return totalScore;
}

void putBlock(int t, int r, int c){
  if(t == 1){
    moveTypeOne(r, c);
  } else if(t == 2){
    moveTypeTwo(r, c);
  } else if(t == 3){
    moveTypeThree(r, c);
  }
}

int countBlocks(){
  int cnt = 0;
  for(int i=0; i<MAX_N; ++i){
    for(int j=0; j<MAX_N; ++j){
      if(i >= RED_MAX && j >= RED_MAX){
        continue;
      }
      cnt += board[i][j];
    }
  }

  return cnt;
}

void solve(){
  int n; cin >> n;
  int score = 0;
  while(n--){
    int t, r, c; cin >> t >> r >> c;
    putBlock(t, r, c);
    score += removeBlocks();
  }

  cout << score << "\n" << countBlocks();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  solve();
  return 0;
}