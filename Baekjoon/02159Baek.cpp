#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

typedef long long ll;

struct pos{
  int r, c;
};

int N;
queue<pos> q;
int dir[5][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};
ll dp[MAX_N+1][5];

void getInput(){
  cin >> N;
  int r, c;
  cin >> r >> c;
  q.push({r, c});

  for(int i=1; i<=N; ++i){
    int cr, cc;
    cin >> cr >> cc;
    q.push({cr, cc});
  }
  for(int i=1; i<=N; ++i){
    for(int j=0; j<5; ++j){
      dp[i][j] = -1;
    }
  }
}

bool checkBound(int r, int c){
  return r < 1 || c < 1 || r > MAX_N || c > MAX_N;
}

ll absFunc(ll x){
  return x > 0 ? x : -x;
}

ll getDistance(pos p1, pos p2){
  return absFunc(p1.r - p2.r) + absFunc(p1.c - p2.c);
}

void updateDp(){
  pos start = q.front();
  q.pop();
  pos next = q.front();
  q.pop();

  for(int i=0; i<5; ++i){
    int nr =  next.r + dir[i][0];
    int nc =  next.c + dir[i][1];
    dp[1][i] = getDistance(start, {nr, nc});
  }
  start = next;

  for(int i=2; i<=N; ++i){
    next = q.front();
    q.pop();
    for(int j=0; j<5; ++j){
      int nr = next.r + dir[j][0];
      int nc = next.c + dir[j][1];
      
      for(int k=0; k<5; ++k){
        int br = start.r + dir[k][0];
        int bc = start.c + dir[k][1];
        ll dist = getDistance({br, bc}, {nr, nc});
        if(dp[i][j] == -1 || dp[i][j] > dp[i-1][k] + dist){
          dp[i][j] = dp[i-1][k] + dist;
        }
      }
    }
    start = next;
  }
}

ll minFunc(ll a, ll b){
  return a < b ? a : b;
}

void printShortest(){
  ll ret = dp[N][0];
  for(int i=1; i<5; ++i){
    ret = minFunc(ret, dp[N][i]);
  }

  cout << ret;
}

void solve(){
  getInput();
  updateDp();
  printShortest();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}