#include <iostream>
#include <map>

using namespace std;

int countClothes(map<string, int> &dress)
{
  int ret = 1;
  for(auto &d: dress)
  {
    ret *= (d.second+1);
  }

  return ret - 1;
}

void getClothes(int &n, map<string, int> &dress)
{
  while(n--)
  {
    string item, itemKind; cin >> item >> itemKind;
    if(dress.find(itemKind) != dress.end())
    {
      ++dress[itemKind];
    }
    else
    {
      dress[itemKind] = 1;
    }
  }
}

void solve()
{
  int testCases; cin >> testCases;
  while(testCases--)
  {
    int n; cin >> n;
    map<string, int> dress;
    getClothes(n, dress);
    int count = countClothes(dress);
    cout << count << "\n";
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}