#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

void getInputs(vector<int> &logs){
    int logCnt; cin >> logCnt;
    while(logCnt--){
        int tempLog; cin >> tempLog;
        logs.push_back(tempLog);
    }
}

vector<int> sortLogs(vector<int> &logs){
    stack<int> rightLogs;
    vector<int> leftLogs, finLogs;

    sort(logs.begin(), logs.end());

    for(int i=0; i<logs.size(); ++i){
        if(i%2){
            leftLogs.push_back(logs[i]);
        } else{
            rightLogs.push(logs[i]);
        }
    }

    for(auto ll : leftLogs){
        finLogs.push_back(ll);
    }
    while(!rightLogs.empty()){
        finLogs.push_back(rightLogs.top());
        rightLogs.pop();
    }

    return finLogs;
}

void solve(){
    vector<int> logs, leftLogs, rightLogs;
    int maxi = 0;
    getInputs(logs);

    vector<int> finLogs = sortLogs(logs);
    for(int i=0; i<finLogs.size()-1; ++i){
        maxi = max(maxi, abs(finLogs[i] - finLogs[i+1]));
    }

    cout << maxi << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testCases; cin >> testCases;
    while(testCases--){
        solve();
    }
    
    return 0;
}