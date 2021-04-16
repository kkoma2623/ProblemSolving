#include <string>
#include <vector>
#include <algorithm>

#define MAX_N 100

using namespace std;

bool visit[MAX_N+1];
int ds[MAX_N+1];
int dsCnt[MAX_N+1];

bool cmp(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

int _find(int node){
    if(ds[node] == node){
        return node;
    }
    
    return _find(ds[node]);
}

void _union(int u, int v){
    u = _find(u);
    v = _find(v);
    
    if(u == v){
        return;
    }
    
    if(dsCnt[u] < dsCnt[v]){
        ds[u] = v;
        dsCnt[u] += dsCnt[v];
    } else{
        ds[v] = u;
        dsCnt[v] += dsCnt[u];
    }
}

bool isCycle(int a, int b){
    
    return _find(a) == _find(b);
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    for(int i=0; i<n; ++i){
        ds[i] = i;
        dsCnt[i] = 1;
    }
    sort(costs.begin(), costs.end(), cmp);
    for(auto cost: costs){
        int first = cost[0];
        int second = cost[1];
        if(isCycle(first, second)){
            continue;
        }
        
        answer += cost[2];
        _union(first, second);
    }
    
    return answer;
}