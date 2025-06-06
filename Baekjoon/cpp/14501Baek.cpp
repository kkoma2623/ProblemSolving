#include <iostream>
#include <vector>

using namespace std;

// dp[i + Ti] = max(dp[i+Ti], dp[i] + Pi)
// dp[i + 1] = dp[i]

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N; cin >> N; // work day
  long long earn[N+1]={0,};
  vector<pair<long long, long long>> sche;
  for(int i=0; i<N; ++i){
    long long t, p; cin >> t >> p;
    sche.push_back({t, p});
  }

  for(int i=0; i<N; ++i){
    if(sche[i].first + i <= N && sche[i].second + earn[i] > earn[i + sche[i].first]){
      // 일 끝나는 날에 초기화
      earn[i + sche[i].first] = sche[i].second + earn[i];

      // 그 뒤에도 최댓값으로 초기화
      for(int j=i + sche[i].first; j<=N; ++j){
        if(earn[j] < earn[i + sche[i].first]){
          earn[j] = earn[i + sche[i].first];
        }
      }
    }
  }
  cout << earn[N];
  return 0;
}