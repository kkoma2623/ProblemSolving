#include <iostream>

#define MAX_N 300

using namespace std;

int N, M;
int G[MAX_N+1][MAX_N+1];
int tempG[MAX_N+1][MAX_N+1];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // r, d, l, u
bool visited[MAX_N+1][MAX_N+1];

void initVisit(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            visited[r][c] = false;
        }
    }
}

void initTempG(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            tempG[r][c] = G[r][c];
        }
    }
}

void temp2G(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            G[r][c] = tempG[r][c];
        }
    }
}

bool checkAllMelted(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            if(G[r][c] > 0) return false;
        }
    }

    return true;
}

void dfs(int r, int c){
    if(visited[r][c]) return;
    visited[r][c] = true;

    for(int i=0; i<4; ++i){
        int nextR = r + dir[i][0], nextC = c + dir[i][1];
        if(nextR < 0 || nextC < 0 || nextR >= N || nextC >= M) continue;
        if(G[r][c] == 0) continue;
        dfs(nextR, nextC);
    }
}

void getInputs(){
    cin >> N >> M;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            cin >> G[r][c];
        }
    }
}

bool checkMoreThan2(){
    int numIce = 0;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            if(visited[r][c]) continue;
            if(G[r][c] == 0) continue;
            ++numIce;
            dfs(r, c);
        }
    }
    return numIce >= 2;
}

void melt(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            if(G[r][c] == 0) continue;
            
            int cntZero = 0;
            for(int i=0; i<4; ++i){
                int nextR = r + dir[i][0], nextC = c + dir[i][1];
                if(nextR < 0 || nextC < 0 || nextR >= N || nextC >= M){
                    continue;
                }
                if(G[nextR][nextC] == 0){
                    ++cntZero;
                }
            }
            
            tempG[r][c] = G[r][c] - cntZero;
            if(tempG[r][c] < 0) {
                tempG[r][c] = 0;
            }
        }
    }
}

void printG(){
    cout << "\n===========\n";
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            cout << G[r][c] << " ";
        }cout << "\n";
    }
}

int solve(){
    getInputs();
    int cntYear = 0;
    int numIce = 0;
    
    if(checkAllMelted()){
        cout << 0;
        return 0;
    }
    if(checkMoreThan2()){
        cout << cntYear;
        return 0;
    }
    initVisit();
    
    while (true){
        ++cntYear;
        melt();
        temp2G();
        if(checkMoreThan2()){
           cout << cntYear;
            return 0;
        }
        initVisit();
        if(checkAllMelted()){
            cout << 0;
            return 0;
        }
        initTempG();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}