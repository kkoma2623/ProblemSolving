#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  long long N; // room
  cin >> N;
  vector<long long> A(N); // applicant
  long long B; // supervisor
  long long C; // supervisor2
  long long ans = 0;
  for(int i=0; i<N; ++i){
    cin >> A[i];
  }
  cin >> B >> C;
  ans += N;

  for(auto iter=A.begin(); iter!=A.end(); ++iter){
    if(*iter-B > 0){
      ans += (*iter-B)/C;
      if((*iter-B)%C != 0){
        ++ans;
      }
    }
  }

  cout << ans;

  return 0;
  
}