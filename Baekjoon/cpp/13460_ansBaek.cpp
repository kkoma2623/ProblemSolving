#include <iostream>
#include <string>
#include <queue>
#include <set>
#define MAXN 10
using namespace std;

struct strt{
    int rx;
    int ry;
    int bx;
    int by;
    int cnt;
};
struct strt_{
    int rx;
    int ry;
    int bx;
    int by;
    bool operator<(const strt_ a) const{
        if(rx != a.rx)
            return rx < a.rx;
        if(ry != a.ry)
            return ry < a.ry;
        if(bx != a.bx)
            return bx < a.bx;
        return by < a.by;
    }
    bool operator>(const strt_ a) const{
        if(rx != a.rx)
            return rx > a.rx;
        if(ry != a.ry)
            return ry > a.ry;
        if(bx != a.bx)
            return bx > a.bx;
        return by > a.by;
    }
    bool operator==(const strt_ a) const{
        return rx == a.rx && ry == a.ry && bx == a.bx && by == a.by;
    }
};
int N, M, R[2], B[2], O[2], ans = -1, dir[4][2] = {{1, 0},{-1, 0},{0, 1},{0, -1}};
char T[MAXN][MAXN];
queue<strt> q;
set<strt_> V;

bool moveR(int& rx, int& ry, int& bx, int& by, int dx, int dy);
bool moveB(int& rx, int& ry, int& bx, int& by, int dx, int dy);

bool moveR(int& rx, int& ry, int& bx, int& by, int dx, int dy){
    if(T[ry][rx] == 'O')
        return false;
    if(T[ry + dy][rx + dx] == '#')
        return false;
    if(T[ry + dy][rx + dx] == 'O'){
        rx += dx; ry += dy;
        return true;
    }
    if(rx + dx == bx && ry + dy == by)
        if(!moveB(rx, ry, bx, by, dx, dy))
            return false;
    rx += dx; ry += dy;
    return true;
}

bool moveB(int& rx, int& ry, int& bx, int& by, int dx, int dy){
    if(T[by][bx] == 'O')
        return false;
    if(T[by + dy][bx + dx] == '#')
        return false;
    if(T[by + dy][bx + dx] == 'O'){
        bx += dx; by += dy;
        return true;
    }
    if(bx + dx == rx && by + dy == ry)
        if(!moveR(rx, ry, bx, by, dx, dy))
            return false;
    bx += dx; by += dy;
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for(int y = 0; y < N; y++){
        string str; cin >> str;
        for(int x = 0; x < M; x++){
            if(str[x] == 'R'){
                R[0] = x;
                R[1] = y;
                T[y][x] = '.';
            }else if(str[x] == 'B'){
                B[0] = x;
                B[1] = y;
                T[y][x] = '.';
            }else{
                if(str[x] == 'O'){
                    O[0] = x;
                    O[1] = y;
                }
                T[y][x] = str[x];
            }
        }
    }
    q.push({R[0], R[1], B[0], B[1], 0});
    V.insert({R[0], R[1], B[0], B[1]});
    while(!q.empty()){
        strt t = q.front();
        q.pop();
        if(t.cnt > 10) // 10번 넘어가면 멈추기
            break;
        if(O[0] == t.rx && O[1] == t.ry){
            if(O[0] != t.bx || O[1] != t.by){
                ans = t.cnt;
                break;
            }
        }
        for(int j = 0; j < 4; j++){
            int rx = t.rx, ry = t.ry, bx = t.bx, by = t.by;
            while(moveR(rx, ry, bx, by, dir[j][0], dir[j][1])){}
            while(moveB(rx, ry, bx, by, dir[j][0], dir[j][1])){}
            strt_ tmp = {rx, ry, bx, by};
            if(V.find(tmp) != V.end()) // 중복 이동 제거
                continue;
            V.insert(tmp);
            q.push({rx, ry, bx, by, t.cnt + 1});
        }
    }
    cout << ans;
    return 0;
}