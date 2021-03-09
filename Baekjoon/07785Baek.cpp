#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int logs;
  cin >> logs;
  map<string, bool> people;
  for(int log=0; log<logs; log++){
    string name, action;
    cin >> name >> action;
    if(action == "enter"){
      people.insert({name, true});
    }
    else{
      people.erase(people.find(name));
    }
  }

  for(auto itr = people.rbegin(); itr != people.rend(); itr++){
    cout << (*itr).first << "\n";
  }
  return 0;
}