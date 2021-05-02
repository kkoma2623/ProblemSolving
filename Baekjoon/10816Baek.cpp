#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> um;

void getInput(){
  int n; cin >> n;
  while(n--){
    int num; cin >> num;
    ++um[num];
  }
}

void printAns(){
  int n; cin >> n;
  while(n--){
    int num; cin >> num;
    cout << um[num] << " ";
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