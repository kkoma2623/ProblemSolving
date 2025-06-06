#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int stackSize;
  cin >> stackSize;
  stack<int> s;
  queue<char> res;

  int pos=0;
  for(int i=0; i<stackSize; i++){
    int val;
    cin >> val;
    if(pos < val){
      while(pos != val){
        s.push(++pos);
        res.push('+');
      }
      s.pop();
      res.push('-');
    }
    else{
      while(!s.empty() && s.top() != val){
        s.pop();
        res.push('-');
      }
      if(!s.empty()){
        s.pop();
        res.push('-');
      }
      else{
        pos = -1;
      }
    }
  }
  
  if(!s.empty() || pos != stackSize){
    cout << "NO";
  }
  else{
    while(!res.empty()){
      cout << res.front() << "\n";
      res.pop();
    }
  }
  return 0;
}