#include <iostream>
#include <vector>

#define MAX_N 50

using namespace std;

int N, L, R;
struct pos{
    int r, c;
};
struct nation{
    int population;
    vector<pos> unions;  
};
nation G[MAX_N+1][MAX_N+1];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void getInputs(){
    cin >> N >> L >> R;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            int temp; cin >> temp;
            G[r][c].population = temp;
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= N || c >= N;
}

void setUnions(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            for(int i=0; i<4; ++i){
                int nextR = r+dir[i][0], nextC = c+dir[i][1];
                if(outOfBound(nextR, nextC)) continue;

                int popuDiff = abs(G[r][c].population - G[nextR][nextC].population);
                if(popuDiff < L || popuDiff > R) continue;
                G[r][c].unions.push_back({nextR, nextC});
            }
        }
    }
}

void movePopu(){
    
}

void solve(){
    getInputs();
    setUnions();

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}