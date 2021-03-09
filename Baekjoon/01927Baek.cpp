#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int testCases;
  cin >> testCases;
  priority_queue<int, vector<int>,  greater<int>> pq;
  for(int testCase=0; testCase<testCases; testCase++){
    int val;
    cin >> val;
    if(val != 0){
      pq.push(val);
    }
    else{
      if(!pq.empty()){
        cout << pq.top() << "\n";
        pq.pop();
      }
      else{
        cout << 0 << "\n";
      }
    }
  }
  return 0;
}