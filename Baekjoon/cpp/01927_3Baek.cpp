#include <iostream>
#include <queue>

#define POP 0

using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> pq;

void getInputs(){
  cin >> N;
}

void solve(){
  getInputs();
  while(N--){
    int temp; cin >> temp;
    if(temp != POP){
      pq.push(temp);
      continue;
    }

    if(pq.empty()){
      cout << "0\n";
      continue;
    }
    int pqTop = pq.top(); pq.pop();
    cout << pqTop << "\n";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}