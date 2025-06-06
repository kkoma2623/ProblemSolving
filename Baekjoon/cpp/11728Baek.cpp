#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<int> a, b;

void getInput(){
  cin >> N >> M;
  for(int i=0; i<N; ++i){
    int tmp; cin >> tmp;
    a.push_back(tmp);
  }
  for(int i=0; i<M; ++i){
    int tmp; cin >> tmp;
    b.push_back(tmp);
  }
}

void printArr(){
  int lp=0, rp=0;
  while(lp < N || rp < M){
    if(lp >= N){
      cout << b[rp++] << " ";
      continue;
    }
    if(rp >= M){
      cout << a[lp++] << " ";
      continue;
    }

    if(a[lp] < b[rp]){
      cout << a[lp++] << " ";
    } else{
      cout << b[rp++] << " ";
    }
  }
}

void solve(){
  getInput();
  printArr();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}