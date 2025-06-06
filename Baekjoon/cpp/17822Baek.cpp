#include <iostream>
#include <vector>
#include <deque>
#define NM 50

using namespace std;
int way[4][2] = {
  {-1, 0}, {1, 0}, {0, -1}, {0, 1}
  };

int g[NM+2][NM+2];
int ans[NM+2][NM+2];
int N, M, T; 

bool lookFour(int row, int col){
  if(ans[row][col] == 0) return false;
  for(int i=0; i<4; ++i){
    if(g[row+way[i][0]][col+way[i][1]] == g[row][col]){
      return true;
    }
    if(col == M){
      if(g[row][1] == g[row][col]){
        return true;
      }
    }
    if(col == 1){
      if(g[row][M] == g[row][col]){
        return true;
      }
    }
  }
  return false;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M >> T;
  vector<pair<int, deque<int>>> circle(N + 1);
  for(int i=1; i<=N; ++i){
    for(int j=0; j<M; ++j){
      int num; cin >> num;
      circle[i].second.push_back(num);
    }
  }

  for(int t=0; t<T; ++t){
    int x, d, k; cin >> x >> d >> k;

    // rotation
    if(d == 0){
      for(int rot=x; rot<=N; rot+=x){
        for(int j=0; j<k; ++j){
          circle[rot].second.push_front(circle[rot].second.back());
          circle[rot].second.pop_back();
        }
      }
    }
    else{
      for(int rot=x; rot<=N; rot+=x){
        for(int j=0; j<k; ++j){
          circle[rot].second.push_back(circle[rot].second.front());
          circle[rot].second.pop_front();
        }
      }
    }

    // update circle
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=M; ++j){
        g[i][j] = circle[i].second[j-1];
        ans[i][j] = circle[i].second[j-1];
      }
    }

    // erase numbers
    bool erased = false;
    long double avg = 0;
    long double count = 0;
    for(int i=1; i<=N; ++i){
      for(int j=1; j<=M; ++j){
        if (ans[i][j] != 0){
          avg += ans[i][j];
          ++count;
        }
        if(lookFour(i, j)){
          erased = true;
          ans[i][j] = 0;
        }
      }
    }
    if(!erased){
      avg /= count;
      for(int i=1; i<=N; ++i){
        for(int j=1; j<=M; ++j){
          if(ans[i][j] == 0) continue;
          if(ans[i][j] < avg){
            ++ans[i][j];
          }
          else if (ans[i][j] > avg){
            --ans[i][j];
          }
        }
      }
    }

    for(int i=1; i<=N; ++i){
      for(int j=0; j<M; ++j){
        circle[i].second[j] = ans[i][j+1];
      }
    }
  }


  long long answer=0;
  for(int i=1; i<=N; ++i){
    for(int j=1; j<=M; ++j){
      answer += ans[i][j];
    }
  }


  cout << answer;
  return 0;
}