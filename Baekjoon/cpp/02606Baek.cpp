#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
bool visit[101];

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  map<int, vector<int>>m;
  int com; cin >> com;
  int edges; cin >> edges;
  for(int i=0; i<edges; ++i){
    int com1, com2; cin >> com1 >> com2;
    m[com1].push_back(com2);
    m[com2].push_back(com1);
  }

  queue<int> q;
  visit[1]=true;
  for(int i=0; i<m[1].size(); ++i){
    q.push(m[1][i]);
  }

  int cnt=0;

  while(!q.empty()){
    int nCom = q.front(); q.pop();
    if(visit[nCom]) continue;
    visit[nCom] = true;

    ++cnt;
    for(int i=0; i<m[nCom].size(); ++i){
      if(visit[m[nCom][i]]) continue;
      q.push(m[nCom][i]);
    }
  }
  cout << cnt;
  return 0;
}