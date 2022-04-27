#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 8
#define MAX_M 8

using namespace std;

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int G[MAX_N+1][MAX_M+1];
int tempG[MAX_N+1][MAX_M+1];
bool visited[MAX_N+1][MAX_M+1];
int N, M;
struct pos{
    int r, c;
};
vector<pos> zeros;

void getInputs(){
    cin >> N >> M;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            cin >> G[r][c];
            if(G[r][c] != 0) continue;
            zeros.push_back({r, c});
        }
    }
}

void fillTempG(pos &p1, pos &p2, pos &p3){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            tempG[r][c] = G[r][c];
        }
    }
    tempG[p1.r][p1.c] = 1;
    tempG[p2.r][p2.c] = 1;
    tempG[p3.r][p3.c] = 1;
}

void initVisited(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            visited[r][c] = false;
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= N || c >= M;
}

void dfs(int &r, int &c){
    if(visited[r][c]) return;
    visited[r][c] = true;
    
    if(tempG[r][c] == 1) return;
    tempG[r][c] = 2;

    for(int i=0; i<4; ++i){
        int nextR = r + dir[i][0], nextC = c + dir[i][1];
        if(outOfBound(nextR, nextC)) continue;
        if(tempG[nextR][nextC] != 0) continue;
        dfs(nextR, nextC);
    }
}

void bfs(){
    queue<pos> zerosQ;

    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            if(tempG[r][c] != 2) continue;
            zerosQ.push({r, c});
        }
    }

    while(!zerosQ.empty()){
        pos curr = zerosQ.front(); zerosQ.pop();
        if(visited[curr.r][curr.c]) continue;
        visited[curr.r][curr.c] = true;

        tempG[curr.r][curr.c] = 2;
        for(int i=0; i<4; ++i){
            int nextR = curr.r + dir[i][0], nextC = curr.c + dir[i][1];
            if(outOfBound(nextR, nextC)) continue;
            if(tempG[nextR][nextC] != 0) continue;
            zerosQ.push({nextR, nextC});
        }
    }
}

int countSafe(){
    int ret = 0;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            if(tempG[r][c] == 0) ++ret;
        }
    }

    return ret;
}

void solve(){
    getInputs();

    int maxi = -1;
    for(int i=0; i<zeros.size()-2; ++i){
        for(int j=i+1; j<zeros.size()-1; ++j){
            for(int k=j+1; k<zeros.size(); ++k){
                fillTempG(zeros[i], zeros[j], zeros[k]);
                initVisited();
                // for(int r=0; r<N; ++r){
                //     for(int c=0; c<M; ++c){
                //         if(tempG[r][c] != 2) continue;
                //         dfs(r, c);
                //     }
                // }
                bfs();
                int safeZones = countSafe();
                maxi = max(maxi, safeZones);
            }
        }
    }

    cout << maxi;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}