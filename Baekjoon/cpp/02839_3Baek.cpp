#include <iostream>

using namespace std;

int dp[5001];
int N;

void getInputs(){
  cin >> N;
  dp[0] = 0;
  dp[1] = 0;
  dp[2] = 0;
  dp[3] = 1;
  dp[4] = 0;
  dp[5] = 1;
}

void solve(){
  getInputs();
  for(int i=6; i<=N; ++i){
    if(dp[i-3] == 0 && dp[i-5] == 0) continue;
    if(dp[i-3] == 0){
      dp[i] = dp[i-5] + 1;
      continue;
    }
    if(dp[i-5] == 0){
      dp[i] = dp[i-3] + 1;
      continue;
    }
    dp[i] = min(dp[i-3], dp[i-5]) + 1;
  }
  if(dp[N] == 0) cout << -1;
  else cout << dp[N];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}