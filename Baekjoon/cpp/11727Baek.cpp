#include <iostream>

#define MAX_N 1000

using namespace std;

int N;

int dp[MAX_N+1];

void getInputs(){
  cin >> N;
  dp[0] = 1;
  dp[1] = 1;
  dp[2] = 3;
}

void solve(){
  getInputs();
  for(int i=3; i<=N; ++i){
    dp[i] = (dp[i-1] + dp[i-2]*2)%10007;
  }
  cout << dp[N] << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}