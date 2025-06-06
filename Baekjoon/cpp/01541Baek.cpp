#include <iostream>
#include <string>

using namespace std;

string sen;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> sen;

  bool found = false;
  int pos = 0;
  int num = 0;
  int tempNum = 0;
  for(; pos<sen.size(); ++pos){
    if(sen[pos] == '-') {
      found = true;
      num += tempNum;
      ++pos;
      break;
    }
    if(sen[pos] == '+') {
      num += tempNum;
      tempNum = 0;
      continue;
    }

    tempNum = tempNum*10 + sen[pos] - '0';
  }
  if(!found) num += tempNum;


  if(found) {
    tempNum = 0;
    for(; pos<sen.size(); ++pos){
      if(sen[pos] > '9' || sen[pos] < '0'){
        num -= tempNum;
        tempNum = 0;
        continue;
      }

      tempNum = tempNum*10 + sen[pos] - '0';
    }

    num -= tempNum;
  }

  cout << num;
  return 0;
}