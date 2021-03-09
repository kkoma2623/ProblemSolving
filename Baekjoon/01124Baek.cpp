#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool nPrime[100001];

vector<int> yaksoo(int n) {
  vector<int> ret;
  int localN = n;
  for(int i=2; ;) {
    if(i > n/2) break;
    if(localN%i != 0 || nPrime[i]) {
      ++i;
      continue;
    }

    localN /= i;
    ret.push_back(i);
  }

  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  nPrime[0] = true;
  nPrime[1] = true;
  for(int i=2; i<=316; ++i){
    for(int j=2; i*j<=100000; ++j){
      nPrime[i*j] = true;
    }
  }

  int a, b; cin >> a >> b;
  int ans = 0;
  for(int i=a; i<=b; ++i){
    vector<int> vec; // 약수 모음

    vec = yaksoo(i);
    if(nPrime[vec.size()]) continue;
    ans += 1;
  }

  std::cout << ans;


  return 0;
}