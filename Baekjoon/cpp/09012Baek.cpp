#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int testCases;
  cin >> testCases;

  for(int testCase=0; testCase<testCases; testCase++){
    string br;
    cin >> br;
    stack<char> s;
    bool nono=false;
    for(int b=0; b<br.size(); b++){
      if(br[b] == '('){
        s.push('(');
      }
      else{
        if(s.empty()){
          cout << "NO\n";
          nono=true;
          break;
        }
        else{
          s.pop();
        }
      }
    }
    if(s.empty() && !nono){
      cout << "YES\n";
    }
    else if(!nono) {
      cout << "NO\n";
    }
    
  }
  return 0;
}