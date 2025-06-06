#include <iostream>

#define MAX_K 10000

using namespace std;

typedef long long ll;

int K, N;
ll lan[MAX_K+1];
ll maxi;

void getInput(){
  cin >> K >> N;
  maxi = 0;
  for(int i=0; i<K; ++i){
    ll num; cin >> num;
    lan[i] = num;
    maxi = max(maxi, num);
  }
}

ll devideLan(ll &n){
  ll ret = 0;
  for(int i=0; i<K; ++i){
    ret += lan[i]/n;
  }

  return ret;
}

void getAns(){
  ll lo = 1;
  ll hi = maxi;
  while(lo <= hi){
    ll mid = (hi+lo)/2;
    ll cnt = devideLan(mid);
    if(cnt >= N){
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