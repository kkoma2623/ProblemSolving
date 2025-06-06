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
int G[MAX_N+1][MAX_N+1]; //{y, x}
vector<dirS> ds;
int dir[5][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
ull ans[4];
int sharkY, sharkX;

void getInputs(){
    cin >> N >> M;
    sharkY = (N+1)/2; sharkX = (N+1)/2;
    
    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){
            cin >> G[y][x];
        }
    }
    for(int i=0; i<M; ++i){
        dirS temp; cin >> temp.d >> temp.s;
        ds.push_back(temp);
    }
}

int getMoveDir(int y, int x){
    int con = N+1;
    if (y == (N+1)/2 && x == (N+1)/2) return 3;
    if (y == (N+1)/2 && x == (N+1)/2 - 1) return 2;
    if(y-x <= 0 && y+x > con) return 1;
    if(y-x >= 1 && y+x < con) return 2;
    if(y+x <= con && y-x < 1) return 3;
    if(y+x >= con && y-x > 0) return 4;

    return 0;
}

bool isOutOfBound(int y, int x){
    return y<1 || x<1 || y>N || x>N;
}

queue<int> blizard(int d, int s){
    for(int i=1; i<=s; ++i){
        int y = sharkY + dir[d][0]*i, x = sharkX + dir[d][1]*i;
        G[y][x] = 0;
    }
    queue<int> q;
    int y = sharkY, x = sharkX - 1;
    while(true){
        if(isOutOfBound(y, x)) break;
        int currNum = G[y][x];
        int moveDir = getMoveDir(y, x);
        int ny = y + dir[moveDir][0], nx = x + dir[moveDir][1];

        if(currNum == 0){
            y = ny; x = nx;
            continue;
        }
        q.push(currNum);
        y = ny; x = nx;
    }

    return q;
}

bool bomb(queue<int> &q){
    bool ret = false;
    queue<int> nextQ;
    if(q.empty()) return ret;
    int cnt = 1, currNum = q.front(); q.pop();

    while(!q.empty()){
        int nextNum = q.front();
        q.pop();
        if(currNum == nextNum){
            ++cnt;
            currNum = nextNum;
            continue;
        }

        if(cnt >= 4){
            ans[currNum] += cnt;
            ret = true;
        } else{
            for(int i=0; i<cnt; ++i){
                nextQ.push(currNum);
            }
        }

        currNum = nextNum;
        cnt = 1;
    }
    if(cnt < 4){
        for(int i=0; i<cnt; ++i){
            nextQ.push(currNum);
        }
    } else{
        ans[currNum] += cnt;
        ret = true;
    }

    while(!nextQ.empty()){
        q.push(nextQ.front());
        nextQ.pop();
    }

    return ret;
}

void compress(queue<int> &q){
    if(q.empty()) return;

    queue<int> nextQ;

    int currNum = q.front(); q.pop();
    int cnt = 1;

    while(!q.empty()){
        int nextNum = q.front();
        q.pop();

        if(currNum == nextNum){
            ++cnt;
            continue;
        }

        nextQ.push(cnt);
        nextQ.push(currNum);
        cnt = 1;
        currNum = nextNum;
    }
    if(cnt > 0){
        nextQ.push(cnt);
        nextQ.push(currNum);
    }

    while(!nextQ.empty()){
        q.push(nextQ.front());
        nextQ.pop();
    }
}

void qToG(queue<int> &q){
    int y = sharkY, x = sharkX - 1;
    
    for(int y=1; y<=N; ++y){
        for(int x=1; x<=N; ++x){
            G[y][x] = 0;
        }
    }

    while(!q.empty()){
        int currNum = q.front();
        q.pop();
        if(isOutOfBound(y, x)) return;
        G[y][x] = currNum;
        
        int moveDir = getMoveDir(y, x);
        int ny = y + dir[moveDir][0], nx = x + dir[moveDir][1];
        y = ny; x = nx;
    }
}

void solve(){
  getInputs();
  for(int i=0; i<ds.size(); ++i){
        int d = ds[i].d, s = ds[i].s;
        queue<int> q = blizard(d, s);
        while(bomb(q)){};
        compress(q);
        qToG(q);
  }
  
  cout << ans[1] + ans[2]*2 + ans[3]*3 << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();

  return 0;
}