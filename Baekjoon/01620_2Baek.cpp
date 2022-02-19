#include <iostream>
#include <map>
#include <string>

using namespace std;

void getPocketmons(int &n, map<int, string> &m, map<string, int> &m2)
{
  for(int i=1; i<=n; ++i)
  {
    string name; cin >> name;
    m.insert({i, name});
    m2.insert({name, i});
  }
}

void searchDict(string &str, map<int, string> &m, map<string, int> &m2, int n)
{
  if('0' <= str[0] && str[0] <= '9')
  {
    cout << m[stoi(str)] << "\n";
  }
  else
  {
    cout << m2[str] << "\n";
  }
}

void solve()
{
  int N, M; cin >> N >> M;
  map<int, string> pocketmonDict;
  map<string, int> pocketmonDict2;
  getPocketmons(N, pocketmonDict, pocketmonDict2);
  while(M--)
  {
    string str; cin >> str;
    searchDict(str, pocketmonDict, pocketmonDict2, N);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}