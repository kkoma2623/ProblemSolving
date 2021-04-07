#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Trie{
  public:
    int cnt;
    map<char, Trie> child;
    
    Trie(){
      cnt = 0;
    }

    void insert(string str, int pos){
      cnt += 1;
      if(pos >= str.size()){
        return;
      }
      if(child.find(str[pos]) == child.end()){
        child[str[pos]] = Trie();
      }
      child[str[pos]].insert(str, pos + 1);
    }

    bool find(string str, int pos){
      if(str.size()-1 == pos){
        return child[str[pos]].cnt > 1;
      }
      if(cnt == 1){
        return false;
      }
      return child[str[pos]].find(str, pos + 1);
    }
};


void getInput(vector<string> &nums){
  int n; cin >> n;
  while(n--) {
    string str; cin >> str;
    nums.push_back(str);
  }
}

void solve(){
  vector<string> nums;
  getInput(nums);
  Trie trie = Trie();
  
  for(auto num: nums){
    trie.insert(num, 0);
  }

  for(int i=0; i<nums.size(); ++i){
    if(trie.find(nums[i], 0)){
      cout << "NO";

      return;
    }
  }

  cout << "YES";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T; cin >> T;

  while(T--){
    solve();

    cout << "\n";
  }

  return 0;
}