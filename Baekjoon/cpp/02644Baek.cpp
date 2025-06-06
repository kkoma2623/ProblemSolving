#include <iostream>
#include <queue>

#define MAX_N 100

using namespace std;

int n, m;
int a, b;
int fam[MAX_N+1][MAX_N+1];
int chon[MAX_N+1];
struct strt{
    int person;
    int cnt;
};

void getInputs(){
    cin >> n >> a >> b >> m;
    for(int i=0; i<m; ++i){
        int child, parent; cin >> parent >> child;
        fam[parent][child] = 1;
    }
}

int bfs(){
    queue<strt> q;
    strt start = {a, 0};
    q.push(start);

    while(!q.empty()){
        strt curr = q.front(); q.pop();
        if(chon[curr.person]) continue;
        if(curr.person == b) return curr.cnt;
        chon[curr.person] = 1;

        for(int i=1; i<=n; ++i){
            if(fam[curr.person][i] == 0 && fam[i][curr.person] == 0) continue;
            if(chon[i]) continue;

            q.push({i, curr.cnt + 1});
        }
    }

    return -1;
}

void solve(){
    getInputs();
    int ret = bfs();
    cout << ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}