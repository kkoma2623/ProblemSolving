#include <iostream>
#include <set>

#define MAX_N 1000000

using namespace std;

int N;
int ds[MAX_N+1];
int dsCnt[MAX_N+1];
// set<int> s;

int _find(int n){
  if(ds[n] == n){
    return n;
  }
  if(ds[n] != n){
    // do nothing
  }
  return _find(ds[n]);
}

void _union(int u, int v){
  u = _find(u);
  v = _find(v);

  if(u == v){
    return;
  }

  if(dsCnt[u] < dsCnt[v]){
    ds[u] = v;
    dsCnt[v] += dsCnt[u];
  } else{
    ds[v] = u;
    dsCnt[u] += dsCnt[v];
  }
}

void initDs(){
  for(int i=1; i<=MAX_N; ++i){
    ds[i] = i;
    dsCnt[i] = 1;
  }
}

void getCmd(){
  char cmd; cin >> cmd;
  if(cmd == 'I'){
    int a, b;
    cin >> a >> b;
    _union(a, b);
  } else{
    int temp; cin >> temp;
    cout << dsCnt[_find(ds[temp])] << "\n";
  }
}

void solve(){
  initDs();
  cin >> N;
  while(N--){
    getCmd();
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}