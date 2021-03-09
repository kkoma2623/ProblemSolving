#include <iostream>
#include <vector>
#define INF_MIN -1000000000
#define INF_MAX 1000000000

using namespace std;
int N;
vector<long long> v;
char op[4] = {'+', '-', '*', '/'};
int opNums[4];
int tempOpNums[4];
long long mmax, mmin;

void syncOpNumns(){
  for(int i=0; i<4; ++i){
    tempOpNums[i] = opNums[i];
  }
}

void syncOpNumns2(int *temp){
  for(int i=0; i<4; ++i){
    tempOpNums[i] = temp[i];
  }
}

long long dfs(long long val, int idx, char oper, bool maxi){
  // exit when at the end
  if(idx == v.size()){
    return val;
  }
  long long ans = val;
  switch(oper){
    case '+':
      ans += v[idx];
      tempOpNums[0] -= 1;
      break;
    case '-':
      ans -= v[idx];
      tempOpNums[1] -= 1;
      break;
    case '*':
      ans *= v[idx];
      tempOpNums[2] -= 1;
      break;
    case '/':
      ans /= v[idx];
      tempOpNums[3] -= 1;
      break;
  }
  if(idx+1 == v.size()){
    return ans;
  }
  
  long long min = INF_MAX;
  long long max = INF_MIN;
  int tempOpNumsInFunc[4] = {tempOpNums[0], tempOpNums[1], tempOpNums[2], tempOpNums[3]};
  for(int i=0; i<4; ++i){
    syncOpNumns2(tempOpNumsInFunc);
    if(tempOpNums[i] > 0){
      long long temp = dfs(ans, idx+1, op[i], maxi);
      if(maxi == false && temp < min){
        min = temp;
      }
      if(maxi == true && temp > max){
        max = temp;
      }
    }
  }

  if(maxi)
    return max;
  else
    return min;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N;
  for(int i=0; i<N; ++i){
    int temp; cin >> temp;
    v.push_back(temp);
  }
  for(int i=0; i<4; ++i){
    opNums[i] = 0;
  }
  cin >> opNums[0] >> opNums[1] >> opNums[2] >> opNums[3];
  

  long long max = INF_MIN, min = INF_MAX;
  // 최대 최소 구하기 dfs
  for(int j=0; j<4; ++j){
    syncOpNumns();
    if(tempOpNums[j] > 0){
      long long tempMax = dfs(v[0], 1, op[j], true);
      syncOpNumns();
      long long tempMin = dfs(v[0], 1, op[j], false);
      if(tempMin < min){
        min = tempMin;
      }
      if(tempMax > max){
        max = tempMax;
      }
    }
  }

  cout << max << "\n" << min;

  return 0;
}