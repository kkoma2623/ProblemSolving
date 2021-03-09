#include <iostream>
#include <algorithm>
#include <queue>
#define MAXN 100000

using namespace std;

int dp[MAXN+1];
int N, K;


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> K;
  if(N==K){
    cout << 0;
    return 0;
  }

  fill(dp, dp + MAXN + 1, -1);
  dp[N] = 0;
  queue<int> q;
  q.push(N);

  while(!q.empty()){
    int num = q.front(); q.pop();

    if(num == K){
      break;
    }

    int rightNum = num+1, leftNum = num-1, doubleNum = num*2;
    if(rightNum <= MAXN && dp[rightNum] == -1){
      dp[rightNum] = dp[num]+1;
      q.push(rightNum);
    }
    if(leftNum >= 0 && dp[leftNum] == -1){
      dp[leftNum] = dp[num]+1;
      q.push(leftNum);
    }
    if(doubleNum <= MAXN && dp[doubleNum] == -1){
      dp[doubleNum] = dp[num]+1;
      q.push(doubleNum);
    }
  }

  cout << dp[K];

  return 0;
}