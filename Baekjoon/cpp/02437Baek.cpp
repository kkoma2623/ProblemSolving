#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> choo;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n; cin >> n;
  for(int i=0; i<n; ++i){
    int tmp; cin >> tmp;
    choo.push_back(tmp);
  }

  sort(choo.begin(), choo.end());
  
  if (choo[0] != 1){
    cout << 1;
    return 0;
  } 
    
  int weight=choo[0];

  for(int i=1; i<choo.size(); ++i){
    if(choo[i] <= weight) {
      weight += choo[i];
      continue;
    }

    if(weight + 1 == choo[i]) {
      weight += choo[i];
      continue;
    } else {
      break;
    }
  }

  cout << weight + 1;

  return 0;
}