#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

int solution(vector<string> str){
  sort(str.begin(), str.end());
  const int maxR = str.size();
  vector<string> twoD;

  for(int r=0; r<maxR; ++r){
    if(r == 0){
      twoD.push_back(str[r]);
      continue;
    }
    if(twoD[twoD.size() - 1] == str[r]){
      continue;
    } else{
      twoD.push_back(str[r]);
    }
  }
  
  const int maxC = str[0].size();
  
  string ss[twoD.size()];
  for(int r=0; r<twoD.size(); ++r){
    string curr = twoD[r];
    ss[r] = curr;
  }

  int pivot[maxC];
  for(int i=0; i<maxC; ++i){
    pivot[i] = 0;
  }
  
  for(int r=0; r<twoD.size(); ++r){
    string s = ss[r];

    for(int c=0; c<maxC; ++c){
      if(pivot[c] == 0){
        if(s[c] == 'O'){
          pivot[c] = r+1;
        }
      }
    }
  }

  int ret = 0;
  for(int i=0; i<maxC; ++i){
    ret = max(ret, pivot[i]);
  }

  return ret;
}

vector<string> getInput(){
  vector<string> v;
  string str; cin >> str;
  while(str != "no"){
    v.push_back(str);
    cin >> str;
  }

  return v;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> v = getInput();
  cout << solution(v);

  return 0;
}