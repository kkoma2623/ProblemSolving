#include <iostream>
#include <vector>
#include <set>

#define MAX_N 5001

using namespace std;

struct info{
  int x, y, r;
};

int ds[MAX_N];
int dsCnt[MAX_N];
info enemy[MAX_N];

int N;

void initializeDs(){
  for(int i=1; i<=N; ++i){
    ds[i] = i;
    dsCnt[i] = 1;
    enemy[i] = {0, 0, 0};
  }
}

int _find(int x){
  if(x == ds[x]) return x;

  return ds[x] = _find(ds[x]); // compress path
}

void _union(int u, int v){
  u = _find(u);
  v = _find(v);

  if(u == v) return; // no need to initial for same set
  
  if(dsCnt[u] < dsCnt[v]){ // u -> v;
    ds[u] = v;
    dsCnt[u] += dsCnt[v];
  } else{ // v -> u
    ds[v] = u;
    dsCnt[v] += dsCnt[u];
  }
}

void distCal(int u, int v){
  int dist = (enemy[u].x - enemy[v].x)*(enemy[u].x - enemy[v].x) + (enemy[u].y - enemy[v].y)*(enemy[u].y - enemy[v].y);
  int distR = (enemy[u].r + enemy[v].r)*(enemy[u].r + enemy[v].r);

  if(dist > distR) return;
  
  _union(u, v);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T; cin >> T;
  while(T--){
    cin >> N;
    initializeDs();
    for(int n=1; n<=N; ++n){
      int x, y, r; cin >> x >> y >> r;
      enemy[n] = {x, y, r};
    }

    for(int i=1; i<N; ++i){
      for(int j=i+1; j<=N; ++j){
        distCal(i, j);
        // distCal(j, i); // for bidirection
      }
    }
    for(int i=1; i<=N; ++i){
      ds[i] = _find(i);
    }
    set<int> s;
    for(int i=1; i<=N; ++i){
      s.insert(ds[i]);
    }

    cout << s.size() << "\n";
  }



  return 0;
}