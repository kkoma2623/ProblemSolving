#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> vec;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  string str; cin >> str;
  vec.push_back(str);
  while(str[(int)str.size()-1] != ']'){
    cin >> str;
    vec.push_back(str);
  }

  return 0;
}