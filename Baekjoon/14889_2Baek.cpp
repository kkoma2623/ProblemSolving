#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 20

using namespace std;

int board[MAX_N+1][MAX_N+1];
int N;
long long mini = 987654321;
vector<vector<int>> combiNums;

void combi(int &r, int idx, vector<int> &checked, int cnt){
    if(idx > N) return;
    if(cnt == r){
        vector<int> temp;
        for(int i=0; i<N; ++i){
            if(!checked[i]) continue;
            temp.push_back(i);
        }
        combiNums.push_back(temp);

        return;
    }
    
    for(int i=idx; i<N; ++i){
        if(checked[i]) continue;

        checked[i] = 1;
        combi(r, i+1, checked, cnt+1);
        checked[i] = 0;
    }
}

void getInputs(){
    cin >> N;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            cin >> board[r][c];
        }
    }
}

void printCombi(){
    for(auto combiNum : combiNums){
        for(auto num : combiNum){
            cout << num << ", ";
        }cout << endl;
    }
}

void calcNum(){
    int combiNumsSize = combiNums.size();
    for(int i=0; i<combiNumsSize / 2; ++i){
        long long sTeam = 0, lTeam = 0;
        for(int j=0; j<N/2; ++j){
            for(int k=j+1; k<N/2; ++k){
                int r = combiNums[i][j], c = combiNums[i][k];
                sTeam += board[r][c] + board[c][r];
            }
        }
        for(int j=0; j<N/2; ++j){
            for(int k=j+1; k<N/2; ++k){
                int r = combiNums[combiNumsSize - i - 1][j], c = combiNums[combiNumsSize - i - 1][k];
                lTeam += board[r][c] + board[c][r];
            }
        }

        mini = min(mini, abs(sTeam - lTeam));
    }
}

void solve(){
    getInputs();
    int midN = N/2;
    vector<int> checked;
    for(int i=0; i<N; ++i){
        checked.push_back(0);
    }
    combi(midN, 0, checked, 0);
    // printCombi();
    calcNum();
    cout << mini;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}