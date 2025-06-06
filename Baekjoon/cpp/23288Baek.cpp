#include <iostream>
#include <deque>
#include <queue>

#define MAX_N 20
#define MAX_M 20
#define BA 0
#define LE 1
#define RI 2
#define FR 3
#define BO 4
#define UP 5
#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3

using namespace std;

int N, M, K;
int G[MAX_N+1][MAX_M+1];
int ba = 2, le = 4, ri = 3, fr = 5, bo = 6, up = 1;
int temp[6];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int direction = 0;
struct pos{
    int r, c;
};
pos dicePos;
int score;

void getInputs(){
    cin >> N >> M >> K;
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=M; ++c){
            cin >> G[r][c];
        }
    }
}

void setTemp(){
    temp[BA] = ba; temp[LE] = le; temp[RI] = ri;
    temp[FR] = fr; temp[BO] = bo; temp[UP] = up;
}

void moveEast(){
    setTemp();
    ba = temp[BA]; le = temp[BO], ri = temp[UP];
    fr = temp[FR]; bo = temp[RI]; up = temp[LE];
}

void moveWest(){
    setTemp();
    ba = temp[BA]; le = temp[UP], ri = temp[BO];
    fr = temp[FR]; bo = temp[LE]; up = temp[RI];
}

void moveSouth(){
    setTemp();
    ba = temp[BO]; le = temp[LE], ri = temp[RI];
    fr = temp[UP]; bo = temp[FR]; up = temp[BA];
}

void moveNorth(){
    setTemp();
    ba = temp[UP]; le = temp[LE], ri = temp[RI];
    fr = temp[BO]; bo = temp[BA]; up = temp[FR];
}

bool outOfBound(int r, int c){
    return r < 1 || c < 1 || r > N || c > M;
}

void setDir(){
    int diceNum = bo;
    int mapNum = G[dicePos.r][dicePos.c];
    if(diceNum == mapNum) return;
    if(diceNum > mapNum){
        direction += 1;
        direction %= 4;
        return;
    }
    if(diceNum < mapNum){
        direction += 3;
        direction %= 4;
        return;
    }
}

void moveDice(){
    pos next = {dicePos.r + dir[direction][0], dicePos.c + dir[direction][1]};
    if(outOfBound(next.r, next.c)){
        direction += 2;
        direction %= 4;
        next = {dicePos.r + dir[direction][0], dicePos.c + dir[direction][1]};
    }
    dicePos = next;
    
    switch(direction){
        case EAST:
            moveEast();
            break;
        case SOUTH:
            moveSouth();
            break;
        case WEST:
            moveWest();
            break;
        case NORTH:
            moveNorth();
            break;
        default:
            break;
    }
}

void bfs(){
    queue<pos> q;
    q.push(dicePos);
    bool visited[N+1][M+1];
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=M; ++c){
            visited[r][c] = false;
        }
    }
    int num = G[dicePos.r][dicePos.c];
    while(!q.empty()){
        pos curr = q.front(); q.pop();
        if(outOfBound(curr.r, curr.c)) continue;
        if(visited[curr.r][curr.c]) continue;
        visited[curr.r][curr.c] = true;
        if(num != G[curr.r][curr.c]) continue;
        score += num;
        for(int i=0; i<4; ++i){
            pos next = {curr.r + dir[i][0], curr.c + dir[i][1]};
            if(outOfBound(next.r, next.c)) continue;
            if(num != G[next.r][next.c]) continue;
            q.push(next);
        }
    }
}

void solve(){
    getInputs();
    dicePos.r = 1, dicePos.c = 1;
    direction = 0;

    while(K--){
        moveDice();
        setDir();
        bfs();
    }

    cout << score;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}