#include <iostream>
#include <map>
#include <string>

using namespace std;

struct pos{
  int r, c;
  bool operator==(pos &p)const{
    return r == p.r && c == p.c;
  }
};

map<char, pos> m;
char lFinger, rFinger;
string sen;

void setKeyboard(){
  m['q'] = {0, 0};
  m['w'] = {0, 1};
  m['e'] = {0, 2};
  m['r'] = {0, 3};
  m['t'] = {0, 4};
  m['y'] = {0, 5};
  m['u'] = {0, 6};
  m['i'] = {0, 7};
  m['o'] = {0, 8};
  m['p'] = {0, 9};
  m['a'] = {1, 0};
  m['s'] = {1, 1};
  m['d'] = {1, 2};
  m['f'] = {1, 3};
  m['g'] = {1, 4};
  m['h'] = {1, 5};
  m['j'] = {1, 6};
  m['k'] = {1, 7};
  m['l'] = {1, 8};
  m['z'] = {2, 0};
  m['x'] = {2, 1};
  m['c'] = {2, 2};
  m['v'] = {2, 3};
  m['b'] = {2, 4};
  m['n'] = {2, 5};
  m['m'] = {2, 6};
}

void getInput(){
  cin >> lFinger >> rFinger;
  cin >> sen;
}

void changeFinger(int nr, int nc, string handType){
  pos nPos = {nr, nc};
  char nHandChar;

  for(const auto& item : m){
    if(item.second == nPos){
      nHandChar = item.first;
      break;
    }
  }

  if(handType == "right"){
    rFinger = nHandChar;
  } else{
    lFinger = nHandChar;
  }
}

int moveFinger(int r, int c, int _c){
  if(c > _c){
    // right hand
    int handR = m[rFinger].r, handC = m[rFinger].c;
    changeFinger(r, c, "right");
    return abs(r - handR) + abs(c - handC);
  }

  // left hand
  int handR = m[lFinger].r, handC = m[lFinger].c;
  changeFinger(r, c, "left");
  return abs(r - handR) + abs(c - handC);
}

int getDist(int r, int c){
  if(r == 2){
    return moveFinger(r, c, 3);
  } else{
    return moveFinger(r, c, 4);
  }
}

int taxiDist(){
  int dist = 0;
  for(int s=0; s<sen.size(); ++s){
    char charkey = sen[s];
    int r = m[charkey].r, c = m[charkey].c;
    dist += getDist(r, c) + 1;
  }

  return dist;
}

void solve(){
  setKeyboard();
  getInput();
  int dist = taxiDist();

  cout << dist;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}