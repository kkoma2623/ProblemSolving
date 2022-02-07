#include <iostream>
#define MAX_N 1000001

using namespace std;

typedef long long ll;

struct strt
{
  ll num;
  bool ee;
};

bool era[MAX_N];
bool eraNoNo[MAX_N];
ll minN;
ll maxN;
strt st[MAX_N];

void getInput()
{
  cin >> minN >> maxN;
}

void makeEra()
{
  for(int i=minN; i<=maxN; ++i)
  {
    st[i-minN].num = i;
    st[i-minN].ee = false;
  }
}

void solve()
{
  getInput();
  makeEra();
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  solve();

  return 0;
}