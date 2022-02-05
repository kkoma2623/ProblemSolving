#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10000

using namespace std;

void getInput(vector<int> &eN, vector<int> &oN){
    int cards; cin >> cards;

    while(cards--){
        int num; cin >> num;
        if(num%2) oN.push_back(num);
        else eN.push_back(num);
    }
}

long long calcSum(vector<int> &v){
    sort(v.begin(), v.end());
    long long ret = 0;
    int vSize = v.size();
    
    for(int i=0; i<vSize/2; ++i)
        ret += v[vSize-i-1];

    return ret;
}

void solve(){
    vector<int> evenNum;
    vector<int> oddNum;
    getInput(evenNum, oddNum);

    long long evenSum = calcSum(evenNum);
    long long oddSum = calcSum(oddNum);
    int evenLeft = 0, oddLeft = 0;

    if(evenNum.size() % 2){
        evenLeft = evenNum[evenNum.size()/2];
        oddLeft = oddNum[oddNum.size()/2];
    }

    long long ret = evenSum + oddSum;
    if(evenLeft < oddLeft) ret += evenLeft;
    else ret += oddLeft;

    cout << ret << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testCases; cin >> testCases;

    for(int i=1; i<=testCases; ++i){
        cout << "#" << i << " ";
        solve();
    }
        
    return 0;
}