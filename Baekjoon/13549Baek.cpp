#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct strt{
  int cnt;
  int num;
  bool operator<(const strt &st)const{
    return st.cnt < cnt;
  }
};

bool dp[100001];
int N, K;

void getInput(){
  cin >> N >> K;
}

void solve(){
  getInput();
  
  priority_queue<strt> pq;
  pq.push({0, N});

  while(!pq.empty()){
    strt curr = pq.top();
    pq.pop();

    if(curr.num == K){
      cout << curr.cnt;

      return;
    }

    if(dp[curr.num]){
      continue;
    }
    dp[curr.num] = true;    

    if(curr.num-1 >= 0) {
      pq.push({curr.cnt + 1, curr.num-1});
    }
    if(curr.num+1 <= K){
      pq.push({curr.cnt + 1, curr.num+1});
    }
    if(curr.num*2 <= K*2 && curr.num*2 <= 100000){
      pq.push({curr.cnt, curr.num*2});
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();

  return 0;
}