#include <iostream>
#include <queue>
#include <stack>

#define MAX_N 100

using namespace std;

int row, col;
int cheeze[MAX_N+1][MAX_N+1];
bool visit[MAX_N+1][MAX_N+1];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
struct strt{
    int r, c;
};
bool isLast;

void getInputs(){
    cin >> row >> col;
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            cin >> cheeze[r][c];
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= row || c >= col;
}

void checkBound(){
    queue<strt> q;
    q.push({0, 0});

    while(!q.empty()){
        strt curr = q.front(); q.pop();
        if(visit[curr.r][curr.c]) continue;
        visit[curr.r][curr.c] = true;

        for(int i=0; i<4; ++i){
            strt next = {curr.r + dir[i][0], curr.c + dir[i][1]};
            if(outOfBound(next.r, next.c)) continue;
            if(visit[next.r][next.c]) continue;
            if(cheeze[next.r][next.c] != 0) {
                cheeze[next.r][next.c] = 'c';
                continue;
            }
            q.push(next);
        }
    }
}

void initVisit(){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            visit[r][c] = false;
        }
    }
}

void removeBound(){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(cheeze[r][c] != 'c') continue;
            cheeze[r][c] = 0;
        }
    }
}

bool checkAllRemoved(){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(cheeze[r][c] == 0) continue;
            return false;
        }
    }
    return true;
}

void checkCheezeSave(){
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(cheeze[r][c] != 1) continue;
            isLast = false;
            return;
        }
    }
}

int countCheeze(){
    int color = 0;
    for(int r=0; r<row; ++r){
        for(int c=0; c<col; ++c){
            if(cheeze[r][c] == 0) continue;
            if(visit[r][c]) continue;
            stack<strt> s;
            s.push({r, c});
            while(!s.empty()){
                strt curr = s.top(); s.pop();
                if(visit[curr.r][curr.c]) continue;
                visit[curr.r][curr.c] = true;
                ++color;
                for(int i=0; i<4; ++i){
                    strt next = {curr.r+dir[i][0], curr.c+dir[i][1]};
                    if(outOfBound(next.r, next.c)) continue;
                    if(cheeze[next.r][next.c] != 1) continue;
                    if(visit[next.r][next.c]) continue;
                    s.push(next);
                }
            }
        }
    }

    return color;
}

void solve(){
    getInputs();
    int cnt = 0;
    int cheezeCnt = 0;
    // while(!checkAllRemoved()){
    while(!isLast){
        ++cnt;
        isLast = true;
        checkBound();
        initVisit();
        checkCheezeSave();
        if(isLast){
            cheezeCnt = countCheeze();
            break;
        }
        // initVisit();
        removeBound();
    }

    std::cout << cnt << "\n" << cheezeCnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}