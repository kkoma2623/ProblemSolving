#include <iostream>
#include <queue>
#include <string>

#define MAX_N 100

using namespace std;

struct cell{
    int r, c;
    int cnt;
};

int maze[MAX_N+1][MAX_N+1];
bool visit[MAX_N+1][MAX_N+1];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int N, M;

void getInputs(){
    for(int i=0; i<N; ++i){
        string str; cin >> str;
        for(int j=0; j<M; ++j){
            maze[i][j] = str[j] - '0';
        }
    }
}

void bfs(){
    queue<cell> q;
    q.push({0, 0, 1});

    while(!q.empty()){
        cell curr = q.front();
        q.pop();
        if(curr.r == N-1 && curr.c == M-1){
            cout << curr.cnt;
            return;
        }
        if(visit[curr.r][curr.c])
            continue;
        visit[curr.r][curr.c] = true;
        for(int i=0; i<4; ++i){
            cell next = {curr.r + dir[i][0], curr.c + dir[i][1], curr.cnt + 1};
            if(next.r < 0 || next.r >= N || next.c < 0 || next.c >= M)
                continue;
            if(visit[next.r][next.c])
                continue;
            if(maze[next.r][next.c] == 0)
                continue;
            q.push(next);
        }
    }
}

void solve(){
    cin >> N >> M;
    getInputs();
    bfs();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}