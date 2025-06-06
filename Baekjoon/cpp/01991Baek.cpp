#include <iostream>

using namespace std;

struct node
{
  char l;
  char r;
};

node nodeList[26];

void pre(int nodeIdx){
  if(nodeIdx + 'A' == '.') return;
  cout << (char)(nodeIdx + 'A');
  if(nodeList[nodeIdx].l || nodeList[nodeIdx].r){
    pre(nodeList[nodeIdx].l - 'A');
    pre(nodeList[nodeIdx].r - 'A');
  }
}

void in(int nodeIdx){
  if(nodeIdx + 'A' == '.') return;
  in(nodeList[nodeIdx].l - 'A');
  cout << (char)(nodeIdx + 'A');
  in(nodeList[nodeIdx].r - 'A');
}

void post(int nodeIdx){
  if(nodeIdx + 'A' == '.') return;
  post(nodeList[nodeIdx].l - 'A');
  post(nodeList[nodeIdx].r - 'A');
  cout << (char)(nodeIdx + 'A');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int nodesCount; cin >> nodesCount;
  for(int i=0; i<nodesCount; ++i){
    char root, l, r; cin >> root >> l >> r;
    nodeList[root-'A'] = {l, r};
  }

  pre(0); cout << "\n";
  in(0); cout << "\n";
  post(0); cout << "\n";

  return 0;
}