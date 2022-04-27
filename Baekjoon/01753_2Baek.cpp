#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_N 20000

using namespace std;

int V, E;
int dist[MAX_N+1];
bool visit[MAX_N+1];
int start;
struct strt{
    int v;
    int w;
    bool operator < (const strt & s)const{
        if(w == s.w) return v < s.v;
        return w < s.w;
    }
    bool operator > (const strt & s)const{
        if(w == s.w) return v > s.v;
        return w > s.w;
    }
};
priority_queue<strt, vector<strt>, greater<strt>> G[MAX_N+1];

void getInputs(){
    cin >> V >> E >> start;
    for(int i=0; i<E; ++i){
        int u, v, w; cin >> u >> v >> w;
        strt temp = {v, w};
        G[u].push(temp);
    }
}

void dijkstra(){
    priority_queue<strt, vector<strt>, greater<strt>> pq;
    pq.push({start, 0});

    while(!pq.empty()){
        strt curr = pq.top(); pq.pop();
        if(visit[curr.v]) continue;
        visit[curr.v] = true;
        dist[curr.v] = curr.w;
        
        while(!G[curr.v].empty()){
            strt next = G[curr.v].top(); G[curr.v].pop();
            if(visit[next.v]) continue;
            pq.push({next.v, dist[curr.v] + next.w});
        }
    }

    for(int i=1; i<=V; ++i){
        if(dist[i] >= 987654321) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
}

void initDist(){
    for(int i=1; i<=V; ++i){
        dist[i] = 987654321;
    }
}

void solve(){
    getInputs();
    initDist();
    dijkstra();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}