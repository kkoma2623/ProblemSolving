#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int N;
ll M;
ll maxi;
vector<int> vec;

void getInput(){
  cin >> N >> M;
  maxi = 0;
  while(N--){
    ll num; cin >> num;
    vec.push_back(num);
    maxi = max(maxi, num);
  }
}

ll getSum(ll &num){
  ll ret = 0;
  for(auto v: vec){
    if(v <= num){
      continue;
    }

    ret += v - num;
  }

  return ret;
}

void getAns(){
  ll lo = 1;
  ll hi = maxi;
  while(lo <= hi){
    ll mid = (lo+hi)/2;
    ll cnt = getSum(mid);
    if(cnt >= M){
      lo = mid + 1;
    } else{
      hi = mid - 1;
    }
  }

  cout << hi;
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