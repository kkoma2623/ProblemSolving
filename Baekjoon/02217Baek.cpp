#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 100000

using namespace std;

vector<long long> ropes;

int ropeCnt = 0;
long long maxi = -1;

void getRopes(){
    for(int i=0; i<ropeCnt; ++i){
        long long tmp; cin >> tmp;
        ropes.push_back(tmp);
    }
}

void getMaxi(){
    for(int i=0; i<ropes.size(); ++i){
        maxi = max(maxi, ropes[i] * (ropeCnt - i));
    }
}

void solve(){
    cin >> ropeCnt;
    getRopes();
    sort(ropes.begin(), ropes.end());
    getMaxi();
    cout << maxi;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();

    return 0;
}