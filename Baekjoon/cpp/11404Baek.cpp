#include <iostream>

#define MAX_N 101
#define MAX_W 2147483647

using namespace std;

int N, M;
long long G[MAX_N][MAX_N];

void initG(int n){
  for(int i=1; i<=n; ++i){
    for(int j=1; j<=n; ++j){
      if(i == j){
        G[i][j] = 0;
        continue;
      }
      G[i][j] = MAX_W;
    }
  }
}

void floyd(int n){
  for(int k=1; k <= n; ++k){
    for(int i=1; i <= n; ++i){
      for(int j=1; j <= n; ++j){
        if(G[i][k] + G[k][j] < G[i][j]){
          G[i][j] = G[i][k] + G[k][j];
        }
      }
    }
  }
}

void printG(int n){
  for(int i=1; i<=n; ++i){
    for(int j=1; j<=n; ++j){
      if(G[i][j] == 2147483647){
        cout << 0 << " ";
      } else {
        cout << G[i][j] << " ";
      }
    }cout << "\n";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;
  initG(N);
  for(int i=0; i<M; ++i){
    int a, b, w; cin >> a >> b >> w;
    if(G[a][b] > w){
      G[a][b] = w;
    }
  }
  floyd(N);
  printG(N);

  return 0;
}