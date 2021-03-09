#include <iostream>
#include <algorithm>

using namespace std;

int dp[5001]={-1, -1, -1, 1, -1, 1, };

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int weight; cin >> weight;

  for(int i=6; i<=weight; ++i){
    if(dp[i-3] == -1 && dp[i-5] == -1) {
      dp[i] = -1;
      continue;
    }
    if(dp[i-3] == -1){
      dp[i] = dp[i-5] + 1;
      continue;
    }
    if(dp[i-5] == -1){
      dp[i] = dp[i-3] + 1;
      continue;
    }

    dp[i] = min(dp[i-3], dp[i-5]) + 1;

  }

  cout << dp[weight];

  return 0;
}