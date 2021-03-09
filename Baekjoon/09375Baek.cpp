#include <iostream>
#include <map>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  int testCases;
  cin >> testCases;
  for(int testCase=0; testCase<testCases; testCase++){
    map<string, int> dress;
    int clothes;
    cin >> clothes;

    for(int cloth=0; cloth<clothes; cloth++){
      string item, itemKind;
      cin >> item >> itemKind;
      if(dress.find(itemKind) != dress.end()){
        dress[itemKind]++;
      }
      else{
        dress[itemKind] = 1;
      }
    }

    int ans = 1;
    for(auto iter = dress.begin(); iter != dress.end(); iter++){
      ans *= (*iter).second+1;
    }

    cout << ans - 1 << "\n";
  }
  return 0;
}