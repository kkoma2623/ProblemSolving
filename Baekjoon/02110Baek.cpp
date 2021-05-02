#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// typedef unsigned long long int;

int N, C;
vector<int> vec;
int maxi;
int mini;

void getInput(){
  cin >> N >> C;
  maxi = 0;
  mini = 987654321;
  while(N--){
    int num; cin >> num;
    vec.push_back(num);
  }
  sort(vec.begin(), vec.end());
  maxi = vec[vec.size()-1];
  mini = vec[0];
}

bool installC(int &num){
  int cnt=1;
  int curr = mini;

  for(int i=1; i<vec.size(); ++i){
    int next = vec[i];
    if(next - curr >= num){
      ++cnt;
      curr = next;
    }
  }

  return cnt >= C;
}

void getAns(){
  int lo = 1;
  int hi = maxi - mini;
  int ans = 0;
  while(lo <= hi){
    int mid = (lo + hi)/2;
    if(installC(mid)){
      lo = mid + 1;
      ans = max(ans, mid);
    } else{
      hi = mid - 1;
    }
  }

  cout << ans;
}

void solve(){
  getInput();
  getAns();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}