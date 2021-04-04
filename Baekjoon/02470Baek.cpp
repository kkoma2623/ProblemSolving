#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct twoNum{
  ll lNum, rNum;
};

vector<ll> v;
int N;

void getInput(){
  cin >> N;
  for(int i=0; i<N; ++i){
    ll temp; cin >> temp;
    v.push_back(temp);
  }
}

twoNum getTwoNums(){
  int lp = 0, rp = N-1;
  twoNum tn = {0, 0};
  ll diff = 2000000002;

  while(lp < rp){
    ll tempDiff = v[lp] + v[rp];
    ll absTempDiff = abs(tempDiff);
    if(absTempDiff == 0){
      tn = {v[lp], v[rp]};

      return tn;
    }

    if(absTempDiff < diff){
      diff = absTempDiff;
      tn = {v[lp], v[rp]};
    }

    if(tempDiff < 0){
      ++lp;
    } else{
      --rp;
    }
  }

  return tn;
}

void solve(){
  getInput();
  sort(v.begin(), v.end());
  twoNum tn = getTwoNums();
  cout << tn.lNum << " " << tn.rNum;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}