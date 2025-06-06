#include <iostream>
#include <queue>

using namespace std;

void minHeap(int &testCases)
{
  priority_queue<int, vector<int>, greater<int> > pq;
  for(int i=0; i<testCases; ++i)
  {
    int val; cin >> val;
    if(val != 0)
    {
      pq.push(val);
    }
    else
    {
      if(!pq.empty())
      {
        cout << pq.top() << "\n";
        pq.pop();
      }
      else
      {
        cout << "0\n";
      }
    }
  }
}

void solve()
{
  int testCases; cin >> testCases;
  minHeap(testCases);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  
  return 0;
}