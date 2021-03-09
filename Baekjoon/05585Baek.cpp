#include <iostream>
#define BILL 1000
using namespace std;

int coins[6] = {500, 100, 50, 10, 5, 1};
int money;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int payed; cin >> payed;
  money = BILL - payed;
  int cnt = 0, pos = 0;
  
  while(money){
    if(money-coins[pos] < 0){
      ++pos;
      continue;
    }
    

    money -= coins[pos];
    ++cnt;
  }

  cout << cnt;
  return 0;
}