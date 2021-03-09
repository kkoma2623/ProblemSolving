#include<iostream>
#include <vector>
#include <queue>

using namespace std;
int main(){
  int computers;
  cin >> computers;
  int edges;
  cin >> edges;
  vector<vector<int> > c(computers);

  for(int i=0; i<edges; i++){
    int a, b;
    cin >> a >> b;
    c[a-1].push_back(b-1);
    c[b-1].push_back(a-1);
  }
  vector<int> visited(computers, 0);
  queue<int> que;
  que.push(0);
  visited[0] = 1;
  int infected =0;
  
  while(que.size() != 0){
    int node = que.front();
    que.pop();
    for(int i=0; i<c[node].size(); i++){
      if(visited[c[node][i]] == 0){
        que.push(c[node][i]);
        infected++;
        visited[c[node][i]] = 1;
      }
    }
  }

  cout << infected;

  return 0;
}