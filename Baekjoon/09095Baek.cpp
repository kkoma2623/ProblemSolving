#include <iostream>
#include <vector>

using namespace std;
int dp[11] = {0, 1, 2, 4, 7, };
int testCases;


int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);
  for (int i=5; i<11; ++i) {
    dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
  }
  cin >> testCases;
  for (int testCase = 0; testCase < testCases; ++testCase) {
    int num; cin >> num;
    cout << dp[num] << "\n";
  }
  return 0;
}