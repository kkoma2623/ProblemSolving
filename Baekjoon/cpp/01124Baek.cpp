#include <iostream>
#include <vector>
#include <cmath>

#define MAX_N 100005

using namespace std;

int primeFac[MAX_N];
bool nPrime[MAX_N];
int A, B;

void eratosthenes(){
  primeFac[0] = primeFac[1] = 1;

  for(int i=2; i<MAX_N; ++i){
    primeFac[i] = i;
  }
  nPrime[0] = nPrime[1] = true;
  for(int i=2; i*i<MAX_N; ++i){
    for(int j=i*2; j<MAX_N; j += i){
      nPrime[j] = true;
    }
  }

  for(int i=2; i*i<MAX_N; ++i){
    if(primeFac[i] == i){
      for(int j=i*i; j<MAX_N; j += i){
        if(primeFac[j] == j){
          primeFac[j] = i;
        }
      }
    }
  }
}

vector<int> factors(int n){
  vector<int> ret;
  while(n > 1){
    ret.push_back(primeFac[n]);
    n /= primeFac[n];
  }

  return ret;
}

int solve(int n){
  eratosthenes();
  int ret = 0;
  while(n <= B){
    vector<int> facs = factors(n++);
    if(!nPrime[(int)facs.size()]){
      ++ret;
    }
  }
  
  return ret;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> A >> B;
  cout << solve(A);
  
  return 0;
}