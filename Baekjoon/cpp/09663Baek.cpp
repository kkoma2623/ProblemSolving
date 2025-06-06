#include <iostream>

#define MAX_N 15

using namespace std;

int N;
int G[MAX_N+1][MAX_N+1];
int checked[MAX_N+1];
int cnt;

void getInputs(){
  cin >> N;
}

bool isSameCol(int r, int c){
  for(int i=r-1; i>=0; --i){
    if(G[i][c] != 0) return true;
  }
  return false;
}

bool isOutOfBound(int r, int c){
  return r<0 || c<0 || r>=N || c>=N;
}

bool isSameX(int r, int c){
  for(int _r = r-1, i=1; _r>=0; --_r, ++i){
    if(checked[_r] + i == c || checked[_r] - i == c) return true;
  }
  return false;
}

void dfs(int n, int r){
  if(n == N){
    ++cnt;
    return;
  }
  for(int i=0; i<N; ++i){
    if(isSameCol(r, i)) continue;
    if(isSameX(r, i)) continue;
    G[r][i] = 1;
    checked[r] = i;
    dfs(n+1, r+1);
    G[r][i] = 0;
    checked[r] = 0;
  }
}

void solve(){
  getInputs();
  dfs(0, 0);
  cout << cnt << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}