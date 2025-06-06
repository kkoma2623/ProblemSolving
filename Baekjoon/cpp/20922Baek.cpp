#include <iostream>
#include <vector>
#include <map>

#define MAX_N 200000

using namespace std;

int N, K;
vector<int> v;
map<int, int> m;
int longest;

void getInput(){
  cin >> N >> K;
  for(int i=0; i<N; ++i){
    int temp; cin >> temp;
    v.push_back(temp);
  }
}

void getLongest(){
  int lp = 0;
  int rp = 0;

  int arrLen = 0;
  while(rp < N){

    if(m[v[rp]] + 1 > K){
      m[v[lp++]] -= 1;
      --arrLen;
      continue;
    }
    ++m[v[rp++]];
    ++arrLen;
    if(arrLen > longest){
      longest = arrLen;
    }
  }
}

void solve(){
  getInput();
  getLongest();
  cout << longest;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}