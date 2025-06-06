#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int monsters, quiz;
  cin >> monsters >> quiz;
  map<string, int> book;
  map<int, string> book2;

  for(int mon=1; mon<=monsters; ){
    string monster;
    cin >> monster;
    book2.insert({mon, monster});
    book.insert({monster, mon++});
  }

  for(int q=0; q<quiz; q++){
    string mon;
    cin >> mon;
    if('0' <= mon[0] && mon[0] <= '9'){
      cout << book2[stoi(mon)] << "\n";
    }
    else{
      cout << book[mon] << "\n";
    }
  }
  return 0;
}