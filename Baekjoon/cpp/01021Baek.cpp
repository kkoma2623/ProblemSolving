#include <iostream>
#include <deque>
#include <queue>

using namespace std;
deque<int> dq;
queue<int> q;

int findIndex(int num) {
  for(int i=0; i<dq.size(); ++i) {
    if (num == dq[i]) return i;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m, n;
  cin >> m >> n;
  for(int i=1; i<=m; ++i){
    dq.push_back(i);
  }
  
  for(int i=0; i<n; ++i) {
    int temp; cin >> temp;
    q.push(temp);
  }

  int ret = 0;
  while(!q.empty()) {
    int index = findIndex(q.front());
    if (index > dq.size()/2) {
      // right
      while(q.front() != dq.front()) {
        int back = dq.back();
        dq.pop_back();
        dq.push_front(back);
        ++ret;
      }
    } else {
      // left
      while(q.front() != dq.front()) {
        int front = dq.front();
        dq.pop_front();
        dq.push_back(front);
        ++ret;
      }
    }

    q.pop();
    dq.pop_front();
  }

  cout << ret;
  return 0;
}