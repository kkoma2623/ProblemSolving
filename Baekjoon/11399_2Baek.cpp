#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> times;

void getInputs(){
    int cnt; cin >> cnt;
    while(cnt--){
        int tempTime; cin >> tempTime;
        times.push_back(tempTime);
    }

    sort(times.begin(), times.end());
}

void countTimes(){
    unsigned long long totalTimes = 0;
    unsigned long long timeSum = 0;
    for(auto t : times){
        timeSum += t;
        totalTimes += timeSum;
    }

    cout << totalTimes;
}

void solve(){
    getInputs();
    countTimes();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}