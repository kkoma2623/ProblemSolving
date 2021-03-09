#include <iostream>
#include <queue>

using namespace std;
int testCases;
int papers, pos;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> testCases;
  for (int i=0; i<testCases; ++i) {
    cin >> papers >> pos;

    priority_queue<int, vector<int>, less<int>> pq;
    queue<int> q;

    for(int j=0; j<papers; ++j) {
      int temp; cin >> temp;
      pq.push(temp);
      q.push(temp);
    }

    int turns = 1;
    while(!pq.empty()) {
      if (pq.top() == q.front()) {
        pq.pop();
        q.pop();
        if (pos == 0) {
          cout << turns << "\n";
          break;
        }
        pos -= 1;
        ++turns;
        continue;
      }

      int temp = q.front();
      q.pop();
      q.push(temp);
      if (pos == 0) pos = q.size() - 1;
      else pos -= 1;
    }
  }
  return 0;
}