#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;


struct strt{
  string num;
  int count;
  bool operator<(const strt &cmp)const{
    return cmp.count < count;
  }
  bool operator>(const strt &cmp)const{
    return cmp.count > count;
  }
};
int T;
bool noPrime[10000];
int dp[10000];
string befNum, aftNum;

void findPrime(){
  for(int i=2; i*i<10000; ++i){
    for(int j=i*2; j<10000; j+=i){
      noPrime[j] = true;
    }
  }
  for(int i=1000; i<10000; ++i){
    dp[i] = 987654321;
  }
}

int strToInt(string str){
  int ret = 0;
  for(int i=1, j=3; i<=1000 && j>=0; i*=10, --j){
    ret += (str[j]-'0')*i;
  }
  return ret;
}

void getInputs(){
  cin >> befNum >> aftNum;
}

void bfs(){
  priority_queue<strt> q;
  q.push({befNum, 0});
  dp[strToInt(befNum)] = 0;

  while(!q.empty()){
    strt curr = q.top(); q.pop();
    if(curr.num == aftNum) return;
    int currNumInt = strToInt(curr.num);

    for(int i=0; i<4; ++i){
      for(int j=0; j<10; ++j){
        strt next = curr;
        next.num[i] = j + '0';
        next.count += 1;
        int nextNumInt = strToInt(next.num);
        if(nextNumInt < 1000) continue;
        if(noPrime[nextNumInt]) continue;
        if(dp[nextNumInt] <= next.count) continue;
        dp[nextNumInt] = next.count;
        q.push(next);
      }
    }
  }
}

void initDp(){
  for(int i=1000; i<10000; ++i){
    dp[i] = MAX_N;
  }
}

void solve(){
  getInputs();
  initDp();
  bfs();

  if(dp[strToInt(aftNum)] >= MAX_N) cout << "Impossible\n";
  else cout << dp[strToInt(aftNum)] << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  findPrime();
  
  int testCases; cin >> testCases;
  while(testCases--)
    solve();

  return 0;
}