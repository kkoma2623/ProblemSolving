#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> times;

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n; cin >> n;
  for(int i=0; i<n; ++i) {
    int tmp; cin >> tmp;
    times.push_back(tmp);
  }
  sort(times.begin(), times.end());

  int ans=0;
  int timeSum = 0;
  for(int i=0; i<times.size(); ++i){
    ans += times[i] + timeSum;
    timeSum += times[i];
  }

  cout << ans;
  return 0;
}