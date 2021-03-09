#include <iostream>
#include <string>
#include <map>
#include <queue>

#define MAX_N 25

using namespace std;

int n;
int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int room[MAX_N+1][MAX_N+1];
bool visit[MAX_N+1][MAX_N+1];

int dfs(int row, int col, int cnt){
  if(row<0 || row >= n || col < 0 || col >= n || visit[row][col]) return 0;
  visit[row][col] = true;
  if(room[row][col] == 0) return 0;
  
  room[row][col] += cnt;
  for(int i=0; i<4; ++i){
    dfs(row+dir[i][0], col+dir[i][1], cnt);
  }

  return 1;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for(int i=0; i<n; ++i){
    string tempStr; cin >> tempStr;
    for(int j=0; j<n; ++j){
      room[i][j] = tempStr[j]-'0';
    }
  }
  int cnt = 0;
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      cnt += dfs(i, j, cnt);
    }
  }

  map<int, int> m;
  for(int i=0; i<n; ++i){
    for(int j=0; j<n; ++j){
      if(room[i][j] != 0){
        ++m[room[i][j]];
      }
    }
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  for(auto iter=m.begin(); iter!=m.end(); ++iter){
    pq.push((*iter).second);
  }

  cout << pq.size() << "\n";

  while(!pq.empty()){
    cout << pq.top() << "\n";
    pq.pop();
  }

  return 0;
}