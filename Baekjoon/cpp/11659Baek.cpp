#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

vector<ull> arrSum;
int M;

void getInput(){
  int N; cin >> N;
  cin >> M;
  ull sumCnt = 0;
  arrSum.push_back(0);
  for(int i=0; i<N; ++i){
    int temp; cin >> temp;
    sumCnt += temp;
    arrSum.push_back(sumCnt);
  }
}

ull calSum(){
  int lp, rp; cin >> lp >> rp;
  --lp;
  
  return arrSum[rp] - arrSum[lp];
}

void solve(){
  getInput();
  for(int i=0; i<M; ++i){
    cout << calSum() << "\n";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}