#include <iostream>
#include <vector>
#include <vector>
#define MAX_N 20

using namespace std;
int N;
int s[MAX_N+1][MAX_N+1];
vector<vector<int>> vec;

void comb(int start, int count, vector<int> v){
  if(count == N/2){
    vec.push_back(v);
    return;
  }
  if(start == N + 1){
    return;
  }
  // start 넣은 것
  v.push_back(start);
  comb(start+1, count+1, v);
  // start 안 넣은 것
  v.pop_back();
  comb(start+1, count, v);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N;
  for(int i=1; i<= N; ++i){
    for(int j=1; j<=N; ++j){
      cin >> s[i][j];
    }
  }
  vector<int> v;
  comb(1, 0, v);

  // vec은 조합 다 들어있음. ex) 1,2,3 // 1,2,4 // ...
  long long min = 987654321;
  for(auto iter=vec.begin(); iter!=vec.end(); ++iter){
    long long start = 0;
    long long link = 0;
    int len = (*iter).size();
    vector<int> linkNum(N+1, 1);
    for(int i=0; i<len-1; ++i){
      for(int j=i+1; j<len; ++j){
        start += s[(*iter)[i]][(*iter)[j]] + s[(*iter)[j]][(*iter)[i]];
        linkNum[(*iter)[i]] = 0;linkNum[(*iter)[j]] = 0;
      }
    }
    
    
    for(int i=1; i<N; ++i){
      for(int j=i+1; j<=N; ++j){
        if(linkNum[i] == 0 || linkNum[j] == 0) continue;
        link += s[i][j] + s[j][i];
      }
    }
    if(start > link){
      long long tempMin = start-link;
      if(tempMin < min){
        min = tempMin;
      }
    }
    else{
      long long tempMin = link-start;
      if(tempMin < min){
        min = tempMin;
      }
    }
  }
  cout << min;

  return 0;
}