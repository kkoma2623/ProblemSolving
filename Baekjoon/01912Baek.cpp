#include <iostream>

using namespace std;

int n;
int maxi;

void getInputs(){
  cin >> n;
  cin >> maxi;
  int beforeSum = maxi;
  
  // dp[i] = max(arr[i], dp[i-1] + arr[i])
  for(int i=1; i<n; ++i){
    int nextNum; cin >> nextNum;
    beforeSum = max(nextNum, nextNum + beforeSum);
    maxi = max(beforeSum, maxi);
  }
}

void solve(){
  getInputs();
  cout << maxi << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}