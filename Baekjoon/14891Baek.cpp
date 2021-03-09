#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

deque<int> gear[5];
deque<int> tempGear[5];

// number, direction, from
void spinGear(pair<int, int> p, int from){
  if(p.first == 0 || p.first == 5) return;
  if(p.first < from){
    // right to left
    if(gear[from][6] == gear[p.first][2]){
      return;
    }
    if(p.second == -1){ // front go back
      int temp = tempGear[p.first].front(); tempGear[p.first].pop_front(); tempGear[p.first].push_back(temp);
    }
    else{
      int temp = tempGear[p.first].back(); tempGear[p.first].pop_back(); tempGear[p.first].push_front(temp);
    }
    spinGear({p.first-1, -p.second}, p.first);
  }
  else{
    // left to right
    if(gear[from][2] == gear[p.first][6]){
      return;
    }
    if(p.second == -1){ // front go back
      int temp = tempGear[p.first].front(); tempGear[p.first].pop_front(); tempGear[p.first].push_back(temp);
    }
    else{
      int temp = tempGear[p.first].back(); tempGear[p.first].pop_back(); tempGear[p.first].push_front(temp);
    }
    spinGear({p.first+1, -p.second}, p.first);
  }
}

void syncGear(){

  for(int i=1; i<=4; ++i){
    for(int j=0; j<8; ++j){
      gear[i][j] = tempGear[i][j];
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  for(int i=1; i<=4; ++i){
    gear[i].clear();
    tempGear[i].clear();
  }
  for(int i=1; i<=4; ++i){
    string str; cin >> str;
    for(int s=0; s<str.length(); ++s){
      tempGear[i].push_back(str[s] - '0');
      gear[i].push_back(str[s] - '0');
    }
  }

  int k; cin >> k;
  vector<pair<int, int>> v; // num, direction
  for(int i=1; i<=k; ++i){
    pair<int, int> p; cin >> p.first >> p.second;
    v.push_back(p);
  }

  syncGear();
  for(int i=0; i<k; ++i){
    // spin gear first
    if(v[i].second == -1){ // front go back
      int temp = tempGear[v[i].first].front(); tempGear[v[i].first].pop_front(); tempGear[v[i].first].push_back(temp);
    }
    else{
      int temp = tempGear[v[i].first].back(); tempGear[v[i].first].pop_back(); tempGear[v[i].first].push_front(temp);
    }

    // if gear no == 1
    if(v[i].first == 1){
      // from 1 -> 2
      spinGear({2, -v[i].second}, 1);
    }
    // else if gear no == 4
    else if(v[i].first == 4){
      // from 4 -> 3
      spinGear({3, -v[i].second}, 4);
    }
    // else gear no == 2, 3
    else{
      // left -> right
      spinGear({v[i].first+1, -v[i].second}, v[i].first);
      // right -> left
      spinGear({v[i].first-1, -v[i].second}, v[i].first);
    }
    syncGear();
  }


  int ans=0, score=1;
  for(int i=1; i<=4; ++i){
    if(gear[i].front() == 1){
      ans += score;
    }
    score*=2;
  }

  cout << ans;

  return 0;
}