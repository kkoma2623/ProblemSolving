#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int nums; cin >> nums;
  vector<int> v(nums);
  for(int i=0; i<nums; ++i){
    cin >> v[i];
  }
  if(v.size() == 1){
    cout << v[0]*v[0];
    return 0;
  }

  sort(v.begin(), v.end());
  cout << v[0]*v[v.size()-1];
  return 0;
}