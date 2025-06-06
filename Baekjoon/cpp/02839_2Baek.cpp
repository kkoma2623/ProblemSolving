#include <iostream>
#include <algorithm>

#define MAX_N 5000

using namespace std;

int dp[MAX_N+1];

void fillDp(int n){
    for(int i=6; i<=n; ++i){
        if(dp[i-3] && dp[i-5]){
            dp[i] = min(dp[i-3], dp[i-5]) + 1;
        } else if(dp[i-3]){
            dp[i] = dp[i-3] + 1;
        } else if(dp[i-5]){
            dp[i] = dp[i-5] + 1;
        }
    }
}

void solve(){
    int inputNum; cin >> inputNum;
    dp[3] = 1;
    dp[5] = 1;
    fillDp(inputNum);

    if(dp[inputNum]){
        cout << dp[inputNum];        
    } else{
        cout << -1;
    }

    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}