#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

map<char, int> mm;
vector<string> savedNum;
vector<int> ans;

bool cmp(const pair<char, int>& a, const pair<char, int>& b) {
  if(a.second < b.second) return a.first < b.first;
  return a.second < b.second;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n; cin >> n;
  for(int i=0; i<n; ++i){
    string temp; cin >> temp;
    savedNum.push_back(temp);
    for(int j=temp.size()-1; j>=0; --j){
      mm[temp[j]] += pow(10, temp.size() - j - 1);
    }
  }

  vector<pair<int, char>> vec;


  for(auto iter = mm.begin(); iter != mm.end(); ++iter){
    vec.push_back({(*iter).second, (*iter).first});
  }

  sort(vec.begin(), vec.end(), greater<pair<int, char>>());
  map<char, int> mmm;
  for(int i=9, j=0; i>=0 && j<vec.size(); --i, ++j) {
    mmm[vec[j].second] = i;
  }

  int ret = 0;
  
  for(int i=0; i<savedNum.size(); ++i){
    int temp = 0;
    for(int j=0; j<savedNum[i].size(); ++j){
      temp = temp*10 + mmm[savedNum[i][j]];
    }
    ret += temp;
  }
  cout << ret;
  return 0;
}