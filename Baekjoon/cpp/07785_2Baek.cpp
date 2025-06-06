#include <iostream>
#include <set>

#define IN "enter"
#define OUT "leave"

using namespace std;

void getLog(int &testCases, set<string> &worker)
{
  while(testCases--)
  {
    string name, status; cin >> name >> status;
    if(status == IN)
    {
      worker.insert(name);
    }
    else
    {
      worker.erase(name);
    }
  }
}

void currentWorkers(set<string> &worker)
{
  for(auto iter = worker.rbegin(); iter != worker.rend(); ++iter)
  {
    cout << *iter << "\n";
  }
}

void solve()
{
  int testCases; cin >> testCases;
  set<string> worker;
  getLog(testCases, worker);
  currentWorkers(worker);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}