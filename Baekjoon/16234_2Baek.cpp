#include <iostream>
#include <vector>

#define MAX_N 50

using namespace std;

struct pos{
    int r, c;
};

struct nation{
    int population;
    bool bound[4];
    vector<pos> unionNations;
};

nation G[MAX_N+1][MAX_N+1];
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int N, L, R;
bool visited[MAX_N+1][MAX_N+1];
vector<pos> moveNations;
int popSum, unionNum;
bool flag;

bool compPop(int curr, int next){
    cout << "abs " << abs(curr-next) << "\n";
    return L <= abs(curr-next) && abs(curr-next) <= R;
}

void getInputs(){
    cin >> N >> L >> R;
    for(int row=0; row<N; ++row){
        for(int col=0; col<N; ++col){
            cin >> G[row][col].population;
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= N || c >= N;
}

void check4Bound(int r, int c, nation &curr){
    for(int i=0; i<4; ++i){
        int nextR = r + dir[i][0], nextC = c + dir[i][1];
        if(outOfBound(nextR, nextC)) continue;

        nation next = G[nextR][nextC];
        if(compPop(curr.population, next.population)){
            curr.unionNations.push_back({nextR, nextC});
            flag = true;
        }
    }
}

void printG(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<N; ++c){
            cout << G[r][c].population << " ";
        } cout << "\n";
    }cout << "\n======\n";
}

void dfs(int currR, int currC){
    if(outOfBound(currR, currC)) return;
    if(visited[currR][currC]) return;
    visited[currR][currC] = true;
    cout << "\nvisit " << currR << ", " << currC << "\n";
    

    // cout << currR << ", " << currC << "\n";
    nation curr = G[currR][currC];
    popSum += curr.population;
    unionNum += 1;
    moveNations.push_back({currR, currC});

    for(int i=0; i<curr.unionNations.size(); ++i){
        int nextR = curr.unionNations[i].r, nextC = curr.unionNations[i].c;
        cout << "go to " << nextR << ", " << nextC << "\n";
        nation next = G[nextR][nextC];
        dfs(nextR, nextC);
    }
}

void solve(){
    getInputs();
    
    flag = true;
    int cntDays = 0;
    while(flag){
        flag = false;
        popSum = 0;
        unionNum = 0;
        
        for(int r=0; r<N; ++r){
            for(int c=0; c<N; ++c){
                // nation curr = G[r][c];
                check4Bound(r, c, G[r][c]);
            }
        }

        for(int r=0; r<N; ++r){
            for(int c=0; c<N; ++c){
                dfs(r, c);
                for(int i=0; i<moveNations.size(); ++i){
                    int currR = moveNations[i].r, currC = moveNations[i].c;
                    G[currR][currC].population = popSum/unionNum;
                }
                for(int i=0; i<moveNations.size(); ++i){
                    moveNations.pop_back();
                }
            }
        }
        for(int r=0; r<N; ++r){
            for(int c=0; c<N; ++c){
                visited[r][c] = false;
            }
        }
        if(flag){
            ++cntDays;
        }
        cout << "\n======\n";
        printG();
    }
    cout << cntDays;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}