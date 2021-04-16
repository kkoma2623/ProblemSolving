#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define MAX_N 10000

using namespace std;

class Buddy{
  public:
    int f1, f2;
};

int N, M, k;
int ds[MAX_N+1];
int friendCost[MAX_N+1];
vector<Buddy> buddy;

void getInput(){
  cin >> N >> M >> k;
  for(int i=1; i<=N; ++i){
    cin >> friendCost[i];
  }
  while(M--){
    int f1, f2;
    cin >> f1 >> f2;
    buddy.push_back({f1, f2});
  }
}

int _find(int v){
  if(ds[v] == v){
    return v;
  }

  return _find(ds[v]);
}

void _union(int a, int b){
  a = _find(a);
  b = _find(b);

  if(a == b){
    return;
  }

  if(friendCost[a] < friendCost[b]){
    for(int i=1; i<=N; ++i){
      if(ds[i] == b){
        ds[i] = a;
      }
    }
  } else if(friendCost[a] == friendCost[b]){
    if(a < b){
      for(int i=1; i<=N; ++i){
        if(ds[i] == b){
          ds[i] = a;
        }
      }
    } else{
        for(int i=1; i<=N; ++i){
        if(ds[i] == a){
          ds[i] = b;
        }
      }
    }
  } else{
    for(int i=1; i<=N; ++i){
      if(ds[i] == a){
        ds[i] = b;
      }
    }
  }
}

void solve(){
  getInput();
  for(int i=1; i<=N; ++i){
    ds[i] = i;
  }
  for(auto bud: buddy){
    _union(bud.f1, bud.f2);
  }

  set<int> s;
  for(int i=1; i<=N; ++i){
    s.insert(ds[i]);
  }

  int money = 0;
  for(auto f: s){
    money += friendCost[f];
  }

  if(money <= k){
    cout << money;
  } else{
    cout << "Oh no";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}