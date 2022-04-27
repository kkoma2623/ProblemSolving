#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define MAX_N 55

using namespace std;

int N, M;
int G[MAX_N+1][MAX_N+1];
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int goDir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
struct pos{
    int r, c;
    int s;
};
struct group{
    int g;
    int cnt;
};
vector<pos> ds;
vector<int> changeDirPos;
map<int, pos> m;
int g1, g2, g3;

void getInputs(){
    cin >> N >> M;
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            cin >> G[r][c];
        }
    }
    for(int i=0; i<M; ++i){
        int d, s; cin >> d >> s;
        ds.push_back({dir[d][0], dir[d][1], s});
    }
}

void setChangeDirPos(){
    vector<int> temp;
    for(int i=1; i<N; ++i){
        temp.push_back(i);
        temp.push_back(i);
    }

    int ret = 0;
    changeDirPos.push_back(ret);
    for(auto t: temp){
        ret += t;
        changeDirPos.push_back(ret);
    }
}

bool outOfBound(int r, int c){
    return (r<1 || c<1 || r>N || c>N);
}

void blizard(int magicNum){
    int r = ds[magicNum].r, c = ds[magicNum].c, s = ds[magicNum].s;
    int sharkR = (N+1)/2, sharkC = (N+1)/2;
    int currR = r + sharkR, currC = c + sharkC;
    for(int i=1; i<=s; ++i){
        if(outOfBound(currR, currC)) return;
        G[currR][currC] = 0;
        currR += r;
        currC += c;
    }
}

void setGIndex(){
    int posNum = 0;
    int posDiff = 0;
    int goDirPos = 0;

    int r = (N+1)/2, c = (N+1)/2;
    pos curr = {r, c};
    for(int i=0; i<N*N; ++i){
        int currPos = i;
        m[i] = curr;
        if(changeDirPos[posNum] == currPos){
            ++goDirPos;
            ++posNum;
        }
        curr = {curr.r + goDir[goDirPos%4][0], curr.c + goDir[goDirPos%4][1]};
    }
}

void printG(){
    cout << "\n=======\n";
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            cout << G[r][c] << " ";
        }cout << "\n";
    }
}

void removeTails(){
    vector<int> v;
    for(int i=N*N-1; i>=0; --i){
        pos curr = m[i];
        if(G[curr.r][curr.c] != 0 && v.size() == 0){
            v.push_back(i);
            continue;
        }
        if(G[curr.r][curr.c] != 0){
            v.push_back(i);
            continue;
        }
        if(i == 0){
            for(auto vv: v){
                v.pop_back();
            }
        }
        if(G[curr.r][curr.c] == 0 && v.size() > 0){
            break;
        }
    }
    for(auto vv: v){
        pos curr = m[vv];
        G[curr.r][curr.c] = 0;
    }
}

void moveBalls(){
    int posDiff = 0;
    for(int i=1; i<N*N; ++i){
        pos curr = m[i];
        if(posDiff+i >= N*N) break;
        pos next = m[i+posDiff];
        while(G[next.r][next.c] == 0 && !outOfBound(next.r, next.c)) {
            ++posDiff;
            next = m[i+posDiff];
        }
        G[curr.r][curr.c] = G[next.r][next.c];
    }
    while(posDiff--){
        pos curr = m[N*N-1-posDiff];
        G[curr.r][curr.c] = 0;
    }
    removeTails();
}

void countBoomGroup(int ballNum, int boomCnt){
    if(ballNum == 1){
        g1 += boomCnt;
    }
    if(ballNum == 2){
        g2 += boomCnt;
    }
    if(ballNum == 3){
        g3 += boomCnt;
    }
}

bool boomBalls(){
    int ballNum = G[m[1].r][m[1].c];
    int idx = 1;
    int boomCnt = 1;
    bool flag = false;
    for(int i=2; i<N*N; ++i){
        pos curr = m[i];
        int currBallNum = G[curr.r][curr.c];
        if(ballNum == currBallNum){
            ++boomCnt;
            continue;
        }

        ballNum = currBallNum;
        if(currBallNum == 0){
            if(boomCnt >= 4){
                int tempI = i-1;
                flag = true;
                ballNum = G[m[tempI].r][m[tempI].c];
                countBoomGroup(ballNum, boomCnt);
                while(boomCnt--){
                    pos now = m[tempI--];
                    G[now.r][now.c] = 0;
                }
            } else{
                boomCnt = 0;
            }
            break;
        }
        if(boomCnt >= 4){
            int tempI = i-1;
            flag = true;
            int removeBallNum = G[m[tempI].r][m[tempI].c];
            countBoomGroup(removeBallNum, boomCnt);
            while(boomCnt--){
                pos now = m[tempI--];
                G[now.r][now.c] = 0;
            }
        }
        boomCnt = 1;
    }
    
    if(boomCnt >= 4){
        int tempI = N*N-1;
        countBoomGroup(ballNum, boomCnt);
        while(boomCnt--){
            pos now = m[tempI--];
            G[now.r][now.c] = 0;
        }
    }

    return flag;
}

void changeBalls(){
    queue<group> q;
    int ballNum = G[m[1].r][m[1].c];
    int sameBallCnt = 1;
    for(int i=2; i<N*N; ++i){
        pos curr = m[i];
        int currBallNum = G[curr.r][curr.c];
        if(currBallNum == 0){
            q.push({ballNum, sameBallCnt});
            sameBallCnt = 0;
            break;
        }
        if(ballNum == currBallNum){
            ++sameBallCnt;
            continue;
        }
        q.push({ballNum, sameBallCnt});
        ballNum = currBallNum;
        sameBallCnt = 1;
    }
    if(sameBallCnt >= 1){
        q.push({ballNum, sameBallCnt});
    }

    int idx = 1;
    while(!q.empty()){
        group currGroup = q.front(); q.pop();
        if(idx > N*N) break;
        pos cntPos = m[idx++];
        pos groupPos = m[idx++];
        G[cntPos.r][cntPos.c] = currGroup.cnt;
        G[groupPos.r][groupPos.c] = currGroup.g;
    }
}

void solve(){
    getInputs();
    setChangeDirPos();
    setGIndex();
    for(int i=0; i<M; ++i){
        blizard(i);
        // cout << "\nafter blizard\n"; printG();
        moveBalls();
        // cout << "\nafter move balls\n"; printG();
        while(boomBalls()){
            // cout << "\nafter boom balls\n"; printG();
            moveBalls();
            // cout << "\nafter move balls\n"; printG();
        };
        changeBalls();
        // cout << "\nafter change balls\n"; printG();
    }
    cout << g1+2*g2+3*g3 << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}