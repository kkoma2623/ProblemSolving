#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<pair<int, int>> conf;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n; cin >> n;
  for (int i=0; i<n; ++i) {
    int end, start; cin >> start >> end;
    conf.push_back({end, start});
  }
  sort(conf.begin(), conf.end());
  int endTime = conf[0].first;
  int cnt = 1;

  for(auto iter=conf.begin() + 1; iter != conf.end(); ++iter){
    if(endTime > (*iter).second) continue;
    
    ++cnt;
    endTime = (*iter).first;
  }
  cout << cnt;
  return 0;
}