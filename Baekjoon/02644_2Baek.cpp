#include <iostream>
#include <queue>

#define MAX_N 100

using namespace std;

int n, m;
int a, b;
int fam[MAX_N+1][MAX_N+1];
int dij[MAX_N+1][MAX_N+1];
bool visit[MAX_N+1];
int dist[MAX_N+1];
struct strt{
    int person;
    int cnt;

    bool operator<(const strt& st)const{
        return cnt < st.cnt;
    }
    bool operator>(const strt& st)const{
        return cnt > st.cnt;
    }
};

void getInputs(){
    cin >> n >> a >> b >> m;
    for(int i=0; i<m; ++i){
        int child, parent; cin >> parent >> child;
        fam[parent][child] = 1;
    }
}

void initDijk(){
    for(int i=1; i<=n; ++i){
        dist[i] = 987654321;
        for(int j=1; j<=n; ++j){
            dij[i][j] = 987654321;
        }
    }
}

int dijkstra(){
    priority_queue<strt, vector<strt>, greater<strt>> pq;
    pq.push({a, 0});
    dij[a][a] = 0;
    dist[a] = 0;
    while(!pq.empty()){
        strt curr = pq.top(); pq.pop();
        if(visit[curr.person]) continue;
        visit[curr.person] = true;
        //update weight
        for(int i=1; i<=n; ++i){
            if(fam[i][curr.person] == 0 && fam[curr.person][i] == 0) continue;
            if(visit[i]) continue;

            dij[curr.person][i] = min(curr.cnt+1, dij[curr.person][i]);
            dij[i][curr.person] = min(curr.cnt+1, dij[i][curr.person]);
            dist[i] = min(dist[i], curr.cnt+1);
            pq.push({i, curr.cnt+1});
        }
    }
    if(dist[b] >= 987654321)
        return -1;
    return dist[b];
}

void printDij(){
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=n; ++j){
            cout << dij[i][j] << " ";
        }cout << "\n";
    }
}

void solve(){
    getInputs();
    initDijk();
    int ret = dijkstra();
    // printDij();
    cout << ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}