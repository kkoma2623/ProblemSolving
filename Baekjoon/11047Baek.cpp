#include <iostream>
#include <stack>

using namespace std;

int N, K;
stack<int> coins;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> K;
  for (int i=0; i<N; ++i) {
    int tmp; cin >> tmp;
    coins.push(tmp);
  }

  int cnt = 0;
  while (K) {
    if (K-coins.top() < 0) {
      coins.pop();
      continue;
    }
    K -= coins.top();
    ++cnt;
  }

  cout << cnt;

  return 0;
}