#include <iostream>

#define MAX_N 500

using namespace std;

int N, M;
int dist[MAX_N+1][MAX_N+1];
int reverseDist[MAX_N+1][MAX_N+1];

void getInputs(){
  cin >> N >> M;
  for(int i=0; i<M; ++i){
    int u, v;
    cin >> u >> v;
    dist[u][v] = 1;
    reverseDist[v][u] = 1;
  }
}

void floyd() {
  for(int w=1; w<=N; ++w){
    for(int from=1; from<=N; ++from){
      if(from == w) continue;
      for(int to=1; to<=N; ++to){
        if(from == to || to == w) continue;

        if(dist[from][to] > dist[from][w] + dist[w][to]){
          dist[from][to] = dist[from][w] + dist[w][to];
        }
      }
    }
  }

  for(int w=1; w<=N; ++w){
    for(int from=1; from<=N; ++from){
      if(from == w) continue;
      for(int to=1; to<=N; ++to){
        if(from == to || to == w) continue;

        if(reverseDist[from][to] > reverseDist[from][w] + reverseDist[w][to]){
          reverseDist[from][to] = reverseDist[from][w] + reverseDist[w][to];
        }
      }
    }
  }
}

void initG(){
  for(int i=1; i<=MAX_N; ++i){
    for(int j=1; j<=MAX_N; ++j){
      dist[i][j] = 987654321;
      reverseDist[i][j] = 987654321;
    }
  }
}

int countG(){
  int ret = 0;
  for(int i=1; i<=N; ++i){
    int canGo = 0;
    for(int j=1; j<=N; ++j){
      if (i == j) continue;
      if (dist[i][j] >= 987654321 && reverseDist[i][j] >= 987654321) break;
      ++canGo;
    }
    if (canGo == (N - 1)) ++ret;
  }

  return ret;
}

void printFloyd(){
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cout << dist[i][j] << " ";
    }cout << "\n";
  }
  cout << "\n==========\n";

  for(int i=1; i<=N; ++i){
    for(int j=1; j<=N; ++j){
      cout << reverseDist[i][j] << " ";
    }cout << "\n";
  }
  cout << "\n==========\n";
}

void solve(){
  initG();
  // printFloyd();
  getInputs();
  // printFloyd();
  floyd();
  // printFloyd();
  cout << countG() << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}