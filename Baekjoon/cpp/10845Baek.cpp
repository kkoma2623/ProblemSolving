#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int testCases;
  cin >>testCases;
  queue<int> q;
  for(int testCase=0; testCase<testCases; testCase++){
    string cmd;
    cin >> cmd;

    if(cmd == "push"){
      int val;
      cin >> val;
      q.push(val);
    }
    else if(cmd == "pop"){
      if(!q.empty()){
        cout << q.front() << "\n";
        q.pop();
      }
      else{
        cout << -1 << "\n";
      }
    }
    else if(cmd == "size"){
      cout << q.size() << "\n";
    }
    else if(cmd == "empty"){
      if(!q.empty()){
        cout << 0 << "\n";
      }
      else{
        cout << 1 << "\n";
      }
    }
    else if(cmd == "front"){
      if(!q.empty()){
        cout << q.front() << "\n";
      }
      else{
        cout << -1 << "\n";
      }
    }
    else if(cmd == "back"){
      if(!q.empty()){
        cout << q.back() << "\n";
      }
      else{
        cout << -1 << "\n";
      }
    }
    else{
      cout << "elliot idiot\n";
    }
  }
  return 0;
}