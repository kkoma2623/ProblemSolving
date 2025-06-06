#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int testCases;
  cin >> testCases;
  deque<int> dq;
  for(int testCase=0; testCase<testCases; testCase++){
    string cmd;
    cin >> cmd;
    if(cmd == "push_back"){
      int val;
      cin >> val;
      dq.push_back(val);
    }
    else if(cmd == "push_front"){
      int val;
      cin >> val;
      dq.push_front(val);
    }
    else if(cmd == "pop_back"){
      if(!dq.empty()){
        cout << dq.back() << "\n";
        dq.pop_back();
      }
      else
        cout << -1 << "\n";
    }
    else if(cmd == "pop_front"){
      if(!dq.empty()){
        cout << dq.front() << "\n";
        dq.pop_front();
      }
      else
        cout << -1 << "\n";
    }
    else if(cmd == "front"){
      if(!dq.empty()){
        cout << dq.front() << "\n";
      }
      else{
        cout << -1 << "\n";
      }
    }
    else if(cmd == "back"){
      if(!dq.empty()){
        cout << dq.back() << "\n";
      }
      else{
        cout << -1 << "\n";
      }
    }
    else if(cmd == "size"){
      cout << dq.size() << "\n";
    }
    else if(cmd == "empty"){
      if(!dq.empty()){
        cout << 0 << "\n";
      }
      else{
        cout << 1 << "\n";
      }
    }
  }
  return 0;
}