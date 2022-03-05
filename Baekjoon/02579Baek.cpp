#include <iostream>
#include <algorithm>

#define MAX_N 300

using namespace std;

int stairCnt;
int stairs[MAX_N+1];
int dp[MAX_N+1];

void getInput(){
    cin >> stairCnt;
    for(int i=1; i<=stairCnt; ++i){
        cin >> stairs[i];
    }
    dp[0] = 0;
    dp[1] = stairs[1];
    dp[2] = stairs[2] + stairs[1];
    dp[3] = max(dp[1], stairs[2]) + stairs[3];
    dp[4] = max(dp[2], dp[1] + stairs[3]) + stairs[4];
    // dp[n] = max(dp[n-2], dp[n-3] + stairs[n-1]) + stairs[n];
}

void dpFunc(){
    for(int i=5; i<=stairCnt; ++i){
        dp[i] = max(dp[i-2], dp[i-3] + stairs[i-1]) + stairs[i];
    }

    cout << dp[stairCnt];
}

void solve(){
    getInput();
    dpFunc();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}