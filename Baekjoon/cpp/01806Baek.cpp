#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull N, S;
vector<ull> v;

void getInput(){
  cin >> N >> S;
  int n = N;
  while(n--){
    ull temp; cin >> temp;
    v.push_back(temp);
  }
}

void solve(){
  getInput();

  ull lp=0, rp=0;
  ull sumNum = 0;
  ull sumLen = 100000001;
  while(rp < N){
    sumNum += v[rp];
    if(sumNum >= S){
      ull diffLen = rp - lp + 1;
      if(sumLen > diffLen){
        sumLen = diffLen;
      }
      sumNum -= v[lp++];
      sumNum -= v[rp];

      continue;
    }

    ++rp;
  }
  
  if(sumLen == 100000001){
    cout << 0;
  } else{
    cout << sumLen;
  }
  return;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}