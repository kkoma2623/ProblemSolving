#include <iostream>
#include <queue>

#define MAX_N 20

using namespace std;

int N;
int G[MAX_N+1][MAX_N+1];
struct pos{
    int r, c;
    int cost;

    bool operator < (const pos &p) const{
        if(cost == p.cost){
            if(r == p.r){
                return c < p.c;
            }
            return r < p.r;
        }
        return cost < p.cost;
    }

    bool operator > (const pos &p) const{
        if(cost == p.cost){
            if(r == p.r){
                return c > p.c;
            }
            return r > p.r;
        }
        return cost > p.cost;
    }
};
pos sharkPos;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int sharkSize;
int ate;
int totalMove;

void getInputs(){
    cin >> N;
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            cin >> G[r][c];
            if(G[r][c] == 9){
                sharkPos.r = r;
                sharkPos.c = c;
            }
        }
    }
}

bool outOfBound(int r, int c){
    return (r < 1 || c < 1 || r > N || c > N);
}

bool eatFish(int r, int c, int fishSize, int cost){
    if(sharkSize <= fishSize) return false;

    G[sharkPos.r][sharkPos.c] = 0;
    sharkPos.r = r, sharkPos.c = c;
    ++ate;
    totalMove += cost;
    G[r][c] = 9;
    if(ate == sharkSize){
        ++sharkSize;
        ate = 0;
    }

    return true;
}

bool checkCanEat(){
    priority_queue<pos, vector<pos>, greater<pos>> pq;
    pq.push({sharkPos.r, sharkPos.c, 0});
    bool visited[MAX_N+1][MAX_N+1];
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            visited[r][c] = false;
        }
    }
    while(!pq.empty()){
        pos curr = pq.top(); pq.pop();
        if(visited[curr.r][curr.c]) continue;
        visited[curr.r][curr.c] = true;

        if(G[curr.r][curr.c] != 0 && G[curr.r][curr.c] != 9 && eatFish(curr.r, curr.c, G[curr.r][curr.c], curr.cost))
            return true;
        
        for(int i=0; i<4; ++i){
            int nextR = curr.r + dir[i][0], nextC = curr.c + dir[i][1];
            if(outOfBound(nextR, nextC)) continue;
            if(G[nextR][nextC] > sharkSize) continue;
            
            pq.push({nextR, nextC, curr.cost+1});
        }
    }
    return false;
}

void solve(){
    getInputs();
    sharkSize = 2;
    ate = 0;
    bool flag = false;
    while(checkCanEat()){
        flag = true;
    }

    if(flag) {
        cout << totalMove;
        return;
    }
    cout << 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}