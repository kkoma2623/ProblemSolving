#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int canAccepts, clicks;
  cin >> canAccepts >> clicks;
  vector<string> v;
  set<string> s;

  for(int click=0; click<clicks; click++){
    string who;
    cin >> who;
    v.push_back(who);
  }

  vector<string> res;
  for(int i=clicks - 1; i>=0; i--){
    if(s.find(v[i]) == s.end()){
      s.insert(v[i]);
      res.push_back(v[i]);
    }
  }
  int ss=res.size();
  for(int student=ss-1; student>ss-1-canAccepts && student>=0; student--){
    cout << res[student] << "\n";
  }
  return 0;
}