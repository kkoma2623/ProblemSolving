#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int N;
set<int> s;
queue<int> q;

void getInputs(){
  cin >> N;
  for(int i=0; i<N; ++i){
    int temp; cin >> temp;
    s.insert(temp);
    q.push(temp);
  }
}

vector<int> getS(){
  vector<int> ret;
  for(auto ss: s){
    ret.push_back(ss);
  }

  return ret;
}

void printOrders(){
  vector<int> sOrder = getS();
  map<int, int> m;
  for(int i=0; i<sOrder.size(); ++i){
    m[sOrder[i]] = i;
  }
  while(!q.empty()){
    int curr = q.front(); q.pop();
    cout << m[curr] << " ";
  } cout << "\n";
}

void solve(){
  getInputs();
  printOrders();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}