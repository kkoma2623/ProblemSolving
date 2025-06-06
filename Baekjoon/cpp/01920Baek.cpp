#include <iostream>
#include <set>

using namespace std;

set<int> s;

void getInput(){
  int n; cin >> n;
  while(n--){
    int num;
    cin >> num;

    s.insert(num);
  }
}

void printAns(){
  int n; cin >> n;
  while(n--){
    int num; cin >> num;
    if(s.find(num) != s.end()){
      cout << "1\n";
    } else{
      cout << "0\n";
    }
  }
}

void solve(){
  getInput();
  printAns();
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}