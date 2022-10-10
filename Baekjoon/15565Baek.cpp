#include <iostream>
#include <vector>

#define MAX_N 1000000
#define RYAN 1
#define APEACH 2

using namespace std;

int mini = 987654321;
int N, K;
int G[MAX_N+1];
vector<int> v;

void getInputs(){
  cin >> N >> K;
  for(int i=0; i<N; ++i){
    cin >> G[i];
    if(G[i] == RYAN){
      v.push_back(i);
      // cout << "i: " << i << "\n";
    }
  }
}

void solve(){
  getInputs();
  if(v.size() < K){
    cout << -1 << "\n";
    return;
  }

  for(int i=0; i<=v.size() - K; ++i){
    // cout << i << "\n";
    mini = min(mini, v[i+K-1]-v[i]+1);
  }
  cout << mini << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}