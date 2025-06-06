#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 50
#define INF 987654321

using namespace std;

struct pos{
    int r, c;
    int cost = 0;
};

int N, M;
int G[MAX_N+1][MAX_N+1], tempG[MAX_N+1][MAX_N+1];
bool visited[MAX_N+1][MAX_N+1];
vector<pos> virus;
int zeros;
int tempZeros;
vector<vector<pos>> selectedVirus;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int mini = INF;

void getInputs(){
    cin >> N >> M;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            cin >> G[r][c];
            tempG[r][c] = G[r][c];
            if(G[r][c] == 2){
                virus.push_back({r, c});
                G[r][c] = -2;
                tempG[r][c] = -2;
            }
            if(G[r][c] == 0){
                ++zeros;
            }
            if(G[r][c] == 1){
                G[r][c] = INF;
                tempG[r][c] = INF;
            }
        }
    }
}

void selectVirus(vector<pos> comb, int r, int depth){
    if(r == 0){
        selectedVirus.push_back(comb);
        return;
    }
    if(depth >= virus.size()){
        return;
    }
    comb.push_back(virus[depth]);
    selectVirus(comb, r-1, depth+1);
    comb.pop_back();
    selectVirus(comb, r, depth+1);
}

bool isOutOfBound(int r, int c){
    return r<0 || c<0 || r>=N || c>=N;
}

int countMin(){
    int ans = 0;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(G[r][c] == -2) continue;
            if(G[r][c] >= INF) continue;
            ans = max(G[r][c], ans);
        }
    }

    return ans;
}

void printG(){
    cout << "\n=====\n";
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(G[r][c] >= INF) cout << "- ";
            else if(G[r][c] == -2) cout << "* ";
            else cout << G[r][c] << " ";
        } cout << "\n";
    }
}

void initVisited(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            visited[r][c] = false;
        }
    }
}

void copyG(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            G[r][c] = tempG[r][c];
        }
    }
}

void bfs(int virusIdx){
    vector<pos> virusGroup = selectedVirus[virusIdx];
    queue<pos> q;
    tempZeros = 0;
    copyG();
    initVisited();
    for(auto v: virusGroup){
        q.push(v);
        G[v.r][v.c] = 0;
        visited[v.r][v.c] = true;
    }
    while(!q.empty()){
        pos curr = q.front(); q.pop();
        if (G[curr.r][curr.c] != -2){
            G[curr.r][curr.c] = curr.cost;
            ++tempZeros;
        }
        for(int i=0; i<4; ++i){
            pos next = {curr.r+dir[i][0], curr.c+dir[i][1], curr.cost+1};
            if(isOutOfBound(next.r, next.c)) continue;
            if(G[next.r][next.c] > 0) continue;
            if(visited[next.r][next.c]) continue;
            visited[next.r][next.c] = true;
            if(G[next.r][next.c] == -2) {
                q.push(next);
                continue;
            };
            q.push(next);
        }
    }
    if(zeros == tempZeros - virusGroup.size()){
        int temp = countMin();
        int tempp = mini;
        mini = min(mini, temp);
        // if (tempp != mini)
            // printG();
    } else{
        // printG();
    }
}

void solve(){
    getInputs();
    vector<pos> temp;
    selectVirus(temp, M, 0);
    for(int idx=0; idx<selectedVirus.size(); ++idx){
        bfs(idx);
    }
    cout << ((mini < INF) ? mini : -1) << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}