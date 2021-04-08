#include <iostream>

#define MAX_N 1000000

using namespace std;

int N, M;
int ds[MAX_N+1];
int dsCnt[MAX_N+1];

void getInput(){
  cin >> N >> M;
  for(int i=1; i<=N; ++i){
    ds[i] = i;
    dsCnt[i] = 1;
  }
}

int _find(int x){
  if(x == ds[x]){
    return x;
  }

  return ds[x] = _find(ds[x]);
}

void _union(int a, int b){
  int u = _find(a);
  int v = _find(b);

  if(u == v){
    return;
  }

  if(dsCnt[u] < dsCnt[v]){
    ds[u] = v;
    dsCnt[u] += dsCnt[v];
  } else{
    ds[v] = u;
    dsCnt[v] += dsCnt[u];
  }
}

void unionFind(){
  int cmd, a, b;

  while(M--){
    cin >> cmd >> a >> b;

    if(cmd == 0){
      // union
      _union(a, b);
      
      continue;
    }

    // find
    int u = _find(a);
    int v = _find(b);

    if(u == v){
      cout << "YES\n";
    } else{
      cout << "NO\n";
    }
  }
}

void solve(){
  getInput();
  unionFind();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}