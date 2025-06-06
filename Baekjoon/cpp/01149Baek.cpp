#include <iostream>
#include <vector>

#define MAX_N 1000

using namespace std;

int N;
int dp[MAX_N+1][3];
vector<int> houseColor[MAX_N+1];

void getInput(){
  cin >> N;
  for(int i=0; i<N; ++i){
    for(int c=0; c<3; ++c){
      int color; cin >> color;
      houseColor[i].push_back(color);
    }
  }
}

void dpFunc(){
  dp[0][0] = houseColor[0][0];
  dp[0][1] = houseColor[0][1];
  dp[0][2] = houseColor[0][2];

  for(int i=1; i<N; ++i){
    dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + houseColor[i][0];
    dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + houseColor[i][1];
    dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + houseColor[i][2];
  }

  cout << min(dp[N-1][0], min(dp[N-1][1], dp[N-1][2]));
}

void solve(){
  getInput();
  dpFunc();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}