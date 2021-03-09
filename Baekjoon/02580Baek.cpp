#include <iostream>

using namespace std;
int sudoku[9][9];

bool checkLine(int num, int row, int col){
  for(int i=0; i<9; ++i){
    if(num == sudoku[row][i]) return false;
  }
  for(int i=0; i<9; ++i){
    if(num == sudoku[i][col]) return false;
  }

  return true;
}

bool checkSquare(int num, int row, int col){
  for(int i=)
}

void fillSudoku(int row, int col){
  if(row >= 9 || col >= 9) return ;
  if(sudoku[row][col] == 0){
    for(int i=1; i<=9; ++i){

    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  for(int i=0; i<9; ++i)
    for(int j=0; j<9; ++j)
      cin >> sudoku[i][j];
  


  return 0;
}