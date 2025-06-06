#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_N 20
#define MAX_M 5
#define BLACK -1
#define VOID -2

using namespace std;

struct pos{
    int r, c;
    int num;
};
struct strt{
    vector<pos> p;
    int rainbow = 0;
    pos pivot = {-1, -1};

    bool operator < (const strt &st)const{
        if(p.size() == st.p.size()){
            if(rainbow == st.rainbow){
                if(pivot.r == st.pivot.r){
                    return pivot.c < st.pivot.c;
                }
                return pivot.r < st.pivot.r;
            }
            return rainbow < st.rainbow;
        }
        return p.size() < st.p.size();
    }

    bool operator > (const strt &st)const{
        if(p.size() == st.p.size()){
            if(rainbow == st.rainbow){
                if(pivot.r == st.pivot.r){
                    return pivot.c > st.pivot.c;
                }
                return pivot.r > st.pivot.r;
            }
            return rainbow > st.rainbow;
        }
        return p.size() > st.p.size();
    }
};
int N, M;
int G[MAX_N+1][MAX_N+1];
int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
bool visited[MAX_N+1][MAX_N+1];
long long score;

void getInputs(){
    cin >> N >> M;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            cin >> G[r][c];
        }
    }
}

int myAbs(int n1, int n2){
    int ret = n1-n2;
    if(ret < 0) ret = -ret;
    return ret;
}

int isSide(pos p1, pos p2){
    return (myAbs(p1.r, p2.r) + myAbs(p1.c, p2.c)) == 1;
}

void initVisited(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            visited[r][c] = 0;
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= N || c >= N;
}

pos findPivot(pos p1, pos p2){
    if(outOfBound(p1.r, p1.c)) return p2;
    if(outOfBound(p2.r, p2.c)) return p1;
    int lhsNum = G[p1.r][p1.c], rhsNum = G[p2.r][p2.c];
    if(lhsNum == BLACK) return p2;
    if(rhsNum == BLACK) return p1;
    if(lhsNum == 0) return p2;
    if(rhsNum == 0) return p1;
    if(p1.r == p2.r){
        if(p1.c < p2.c) return p1;
        return p2;
    }
    if(p1.r < p2.r) return p1;
    return p2;
}

void initRainbowVisit(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(G[r][c] == 0) visited[r][c] = false;
        }
    }
}

strt findBlockGroup(int r, int c){
    queue<pos> q;
    q.push({r, c});
    strt ret;
    int num = G[r][c];

    while(!q.empty()){
        pos curr = q.front(); q.pop();
        if(outOfBound(curr.r, curr.c)) continue;
        if(visited[curr.r][curr.c]) continue;
        visited[curr.r][curr.c] = true;
        if(G[curr.r][curr.c] <= BLACK) continue;
        if(G[curr.r][curr.c] != 0) num = G[curr.r][curr.c];
        if(G[curr.r][curr.c] == 0) ret.rainbow += 1;
        ret.pivot = findPivot(ret.pivot, curr);
        ret.p.push_back(curr);
        for(int i=0; i<4; ++i){
            pos next = {curr.r + dir[i][0], curr.c + dir[i][1]};
            if(outOfBound(next.r, next.c)) continue;
            if(G[next.r][next.c] <= BLACK) continue;
            if(num == 0){
                q.push(next);
                continue;
            }
            if(num == G[next.r][next.c] || G[next.r][next.c] == 0) q.push(next);
        }
    }
    initRainbowVisit();

    return ret;
}

strt findBigBlock(){
    initVisited();
    vector<strt> blockGroups;
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(G[r][c] == BLACK) continue;
            if(G[r][c] == 0) continue;
            strt temp = findBlockGroup(r, c);
            blockGroups.push_back(temp);
        }
    }
    sort(blockGroups.rbegin(), blockGroups.rend());
    // std::cout << "pivot " << blockGroups[0].pivot.r << ", " << blockGroups[0].pivot.c << "\n";
    strt temp;
    if(blockGroups.size() <= 0) return temp;
    return blockGroups[0];
}

void printG(){
    cout << "\n====\n";
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(G[r][c] == VOID){
                cout << "   ";
                continue;
            }
            cout << G[r][c] << " ";
            if(G[r][c] >= 0){
                cout << " ";
            }
        }cout << "\n";
    }
}

void gravity(){
    for(int c=0; c<N; ++c){
        for(int r=N-1; r>0; --r){
            if(G[r][c] != VOID) continue;
            pos here = {r, c};
            pos from;
            int metBlack = -1;
            bool metG = false;

            for(int j=r-1; j>=0; --j){
                if(G[j][c] == BLACK){
                    metBlack = j;
                    break;
                }
                if(G[j][c] == VOID) continue;
                metG = true;
                from = {j, c};
                break;
            }

            if(metBlack != -1) {
                r = metBlack;
                continue;
            }
            if(!metG) break;
            if(outOfBound(here.r, here.c)) continue;
            if(outOfBound(from.r, from.c)) continue;
            G[here.r][here.c] = G[from.r][from.c];
            G[from.r][from.c] = VOID;
        }
    }
}

void rotate(){
    queue<int> temp;
    for(int c=N-1; c>=0; --c){
        for(int r=0; r<N; ++r){
            temp.push(G[r][c]);
        }
    }
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            if(temp.empty()) break;
            int curr = temp.front(); temp.pop();
            G[r][c] = curr;
        }
    }
}

void solve(){
    getInputs();
    while(true){
        strt bigBlock = findBigBlock();
        long long cnt = 0;
        int flag = false;
        if(bigBlock.p.size() < 2) break;
        for(auto bb: bigBlock.p){
            if(outOfBound(bb.r, bb.c)) continue;
            G[bb.r][bb.c] = VOID;
            ++cnt;
            flag = true;
        }
        if(!flag) break;
        score += (cnt*cnt);
        // cout << "after remove block\n"; printG();
        gravity();
        // cout << "after gravity\n"; printG();
        rotate();
        // cout << "after rotate\n"; printG();
        gravity();
        // cout << "after gravity\n"; printG();
        // printG();
    }
    cout << score << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}