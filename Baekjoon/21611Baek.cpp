#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 49
#define MAX_M 100

using namespace std;

typedef unsigned long long ull;

struct dirS{
    int d, s;
};
struct pos{
    int r, c;
    bool operator==(const pos &cmp)const{
        return r == cmp.r && c == cmp.c;
    }
};

int N, M;
int G[MAX_N+1][MAX_N+1];
vector<dirS> ds;
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int sharkR, sharkC;
ull ones, twos, threes;

void moveG(queue<int> q);
void printG();

void getInputs(){
    cin >> N >> M;
    sharkR = (N+1)/2; sharkC = (N+1)/2;
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            cin >> G[r][c];
        }
    }
    for(int i=0; i<M; ++i){
        dirS temp; cin >> temp.d >> temp.s;
        ds.push_back(temp);
    }
}

int getMoveDir(int r, int c){
    int con = N+1;
    if (r == (N+1)/2 && c == (N+1)/2) return 3;
    if (r == (N+1)/2 && c == (N+1)/2 - 1) return 2;
    if(r-c <= 0 && r+c > con) return 1;
    if(r-c >= 1 && r+c < con) return 2;
    if(r+c <= con && r-c < 1) return 3;
    if(r+c >= con && r-c > 0) return 4;

    return 0;
}

bool isOutOfBound(int r, int c){
    return r<1 || c<1 || r>N || c>N;
}

void countBallNums(int bn){
    switch(bn){
        case 1:
            ++ones;
            return;
        case 2:
            ++twos;
            return;
        case 3:
            ++threes;
            return;
        default:
            return;
    }
}

bool boom(){
    queue<int> q;
    q.push(G[(N+1)/2][(N+1)/2]);
    pos curr = {(N+1)/2, (N+1)/2};
    queue<int> balls;
    bool ret = false;

    while(true){
        int dirIdx = getMoveDir(curr.r, curr.c);
        pos next = {curr.r + dir[dirIdx][0], curr.c + dir[dirIdx][1]};
        int currNum = q.front();
        if(currNum == G[next.r][next.c]){
            q.push(G[next.r][next.c]);
            curr = next;
            continue;
        }
        if(G[next.r][next.c] == 0) break;
        
        if(q.size() >= 4){
            int ballNum = q.front();
            ret = true;
            while(!q.empty()){
                q.pop();
                countBallNums(ballNum);
            }
        } else{
            while(!q.empty()){
                balls.push(q.front());
                q.pop();
            }
        }
        q.push(G[next.r][next.c]);
        curr = next;
    }
    if(q.size() >= 4){
        ret = true;
        int ballNum = q.front();
        while(!q.empty()){
            countBallNums(ballNum);
            q.pop();
        }
    }
    while(!q.empty()){
        balls.push(q.front());
        q.pop();
    }

    moveG(balls);
    
    return ret;
}

void moveG(queue<int> q){
    pos curr = {(N+1)/2, (N+1)/2};
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            G[r][c] = 0;
        }
    }
    while(!q.empty()){
        if(isOutOfBound(curr.r, curr.c)) return;
        int dirIdx = getMoveDir(curr.r, curr.c);
        int currNum = q.front(); q.pop();
        G[curr.r][curr.c] = currNum;

        pos next = {curr.r + dir[dirIdx][0], curr.c + dir[dirIdx][1]};
        curr = next;
    }
}

void blizard(int d, int s){
    queue<pos> posQ;
    for(int i=1; i<=s; ++i){
        int r = sharkR + dir[d][0]*i, c = sharkC + dir[d][1]*i;
        if(isOutOfBound(r, c)) return;
        G[r][c] = 0;
        posQ.push({r, c});
    }

    pos curr = {(N+1)/2, (N+1)/2};
    queue<int> q;
    q.push(0);

    while(true){
        if(!posQ.empty()){
            pos pq = posQ.front();
            if(pq == curr){
                posQ.pop();
                int dirIdx = getMoveDir(curr.r, curr.c);
                curr = {curr.r + dir[dirIdx][0], curr.c + dir[dirIdx][1]};
                continue;
            }
        }
        if(G[curr.r][curr.c] != 0){
            q.push(G[curr.r][curr.c]);
        }
        
        int dirIdx = getMoveDir(curr.r, curr.c);
        curr = {curr.r + dir[dirIdx][0], curr.c + dir[dirIdx][1]};
        if(curr.r == 1 && curr.c == 1) {
            // cout << "???????\n";
            if(G[curr.r][curr.c] != 0){
                q.push(G[curr.r][curr.c]);
            }
            break;
        }
        // if(isOutOfBound(curr.r, curr.c)) break;
    }

    moveG(q);
}

void printG(){
    cout << "=====\n";
    for(int r=1; r<=N; ++r){
        for(int c=1; c<=N; ++c){
            cout << G[r][c] << " ";
        }cout << "\n";
    }
    cout << "=====\n";
}

void copyBalls(){
    // 상어 오른쪽에서 시작
    pos curr = {(N+1)/2, (N+1)/2 -1};

    // 상어는 넣어주고 시작
    queue<int> q; q.push(0);
    queue<int> sameQ;
    // 상어 오른쪽도 넣어주고 시작
    sameQ.push(G[curr.r][curr.c]);

    while(true){
        // r<1 || c<1 || r>N || c>N;
        if(isOutOfBound(curr.r, curr.c)) break;
        // 복사기 때문에 0을 만나면 멈춘다.
        if(G[curr.r][curr.c] == 0) break;

        // 같은 구슬들 번호
        int beforeNum = sameQ.front();
        // 상하좌우 움직여야하는 dir의 index
        int dirIdx = getMoveDir(curr.r, curr.c);

        // 다음 칸의 r, c
        pos next = {curr.r+dir[dirIdx][0], curr.c+dir[dirIdx][1]};

        // 다음 칸의 
        int currNum = G[next.r][next.c];
        
        curr = next;
        
        if(beforeNum == currNum){
            sameQ.push(currNum);
            continue;
        }

        q.push(sameQ.size());
        q.push(sameQ.front());
        while(!sameQ.empty()){
            sameQ.pop();
        }
        sameQ.push(currNum);
    }
    if(!sameQ.empty() && sameQ.front() != 0){
        q.push(sameQ.size());
        q.push(sameQ.front());
        while(!sameQ.empty()){
            sameQ.pop();
        }
    }

    moveG(q);
}

void solve(){
  getInputs();
  for(auto magic: ds){
      blizard(magic.d, magic.s);
      cout << "bliz\n";
      printG();
      while(boom()){};
      cout << "boom\n";
      printG();
      copyBalls();
      cout << "compress\n";
      printG();
  }
  cout << ones + 2*twos + 3*threes << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}