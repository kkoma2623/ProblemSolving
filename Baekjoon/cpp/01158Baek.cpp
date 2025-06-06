#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int num, step;
  cin >> num >> step;
  vector<int> v;
  
  for(int i=1; i<=num; i++)
    v.push_back(i);
  
  vector<int> res;
  int pos = step-1;

  while(!v.empty()){
    if(pos >= v.size()){
      pos -= v.size();
      continue;
    }
    else{
      res.push_back(v[pos]);
      v.erase(v.begin() + pos);
      pos += step-1;
    }
  }

  cout << '<';
  for(auto iter=res.begin(); iter!=res.end()-1; iter++){
    cout << (*iter) << ", ";
  }
  cout << res[res.size()-1] << '>';
  
  return 0;
}