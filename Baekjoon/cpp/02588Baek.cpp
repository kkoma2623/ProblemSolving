#include <iostream>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int firstNum, secondNum;
  cin >> firstNum >> secondNum;
  int result = firstNum * secondNum;
  while(secondNum){
    cout << firstNum * (secondNum%10) << "\n";
    secondNum /= 10;
  }
  cout << result;
  return 0;
}