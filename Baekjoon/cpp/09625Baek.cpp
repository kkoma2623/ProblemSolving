#include <iostream>

using namespace std;

int N;
int dsA, dsB;

void getInputs(){
  cin >> N;
  dsA = 1;
  dsB = 0;
}

void solve(){
  getInputs();
  for(int i=0; i<N; ++i){
    int tempA = dsB;
    int tempB = dsA + dsB;
    dsA = tempA;
    dsB = tempB;
  }
  cout << dsA << " " << dsB << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}