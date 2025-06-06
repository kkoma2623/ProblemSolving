#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define MAX_N 500000

using namespace std;

int N, P;
vector<pair<int, int>> frets;
map<int, stack<int>> gStrings;
// stack<int> gStrings[MAX_N+1];
long long cnt = 0;

void getInputs(){
    cin >> N >> P;
    for(int i=0; i<N; ++i){
        pair<int, int> temp; cin >> temp.first >> temp.second;
        frets.push_back(temp);
    }
}

void playG(){
    for(auto fret : frets){
        int gN = fret.first, gFret = fret.second;
        if(gStrings[gN].empty()){
            ++cnt;
            gStrings[gN].push(gFret);
            continue;
        }
        
        while(!gStrings[gN].empty() && gFret < gStrings[gN].top()){
            gStrings[gN].pop();
            ++cnt;
        }
        if(!gStrings[gN].empty() && gFret != gStrings[gN].top()){
            gStrings[gN].push(gFret);
            ++cnt;
        } else if(!gStrings[gN].empty()){
            continue;
        } else if(gStrings[gN].empty()){
            gStrings[gN].push(gFret);
            ++cnt;
        }
    }
}

void solve(){
    getInputs();
    playG();
    cout << cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}