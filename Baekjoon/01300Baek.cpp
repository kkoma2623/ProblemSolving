#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull N;
ull k;

void getInputs(){
  cin >> N >> k;
}

ull countLessNums(ull mid){
  ull sum = 0;
  for(ull i=1; i<=N; ++i){
    sum += min(mid/i, N);
  }
  return sum;
}

ull binSearch(){
  ull lP = 1, hP = N*N;
  ull ret = (lP + hP)/2;
  while(lP <= hP){
    ull mP = (lP+hP)/2;
    ull lessNums = countLessNums(mP);
    if (lessNums < k){
      lP = mP + 1;
    } else {
      hP = mP - 1;
      ret = mP;
    }
  }

  return ret;
}

void solve(){
  getInputs();
  cout << binSearch() << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}