#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> k;
int maxi;

void getInputs(){
    cin >> N;
    int temp; cin >> temp;
    for(int i=0; i<temp; ++i){
        int t; cin >> t;
        k.push_back(t);
    }
}

void dfs(int currNum){
    if(currNum > N)
        return;
    maxi = max(currNum, maxi);
    for(int i=0; i<k.size(); ++i){
        dfs(currNum*10 + k[i]);
    }
}

void solve(){
    getInputs();
    dfs(0);
    cout << maxi << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}