#include <iostream>
#include <stack>

using namespace std;

stack<int> stk;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N; cin >> N;
  for(int i=0; i<N; ++i) {
    int temp; cin >> temp;
    if (temp == 0) {
      stk.pop();
      continue;
    }
    stk.push(temp);
  }

  int ssum = 0;
  while(!stk.empty()) {
    ssum += stk.top();
    stk.pop();
  }

  cout << ssum;
  return 0;
}