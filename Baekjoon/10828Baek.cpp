#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int tests;
  cin >> tests;
  stack<int> s;
  for(int test=0; test<tests; test++){
    string cmd;
    cin >> cmd;
    
    if(cmd == "push"){
      int val;
      cin >> val;
      s.push(val);
    }
    else if(cmd == "pop"){
      if(!s.empty()){
        cout << s.top() << "\n";
        s.pop();
      }
      else {
        cout << -1 << "\n";
      }
    }
    else if(cmd == "size"){
      cout << s.size() << "\n";
    }
    else if(cmd == "empty"){
      s.empty() ? cout << "1\n" : cout << "0\n";
    }
    else if(cmd == "top"){
      if(!s.empty())
        cout << s.top() << "\n";
      else
        cout << -1 << "\n";
    }
    else{
      cout << "elliot idiot\n";
    }
  }

  return 0;
}