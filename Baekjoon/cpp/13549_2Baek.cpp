#include <iostream>
#include <queue>

#define MAX_N 100000

using namespace std;

int N, K;
bool visited[MAX_N+MAX_N];
struct strt{
    int pos;
    int cost;

    bool operator < (const strt &s)const{
        return cost > s.cost;
    }
    bool operator > (const strt &s)const{
        return cost < s.cost;
    }
};

void bfs(){
    priority_queue<strt> q;
    q.push({N, 0});

    while(!q.empty()){
        strt curr = q.top(); q.pop();
        if(curr.pos == K){
            cout << curr.cost;
            return;
        }
        if(visited[curr.pos]) continue;
        visited[curr.pos] = true;

        if(curr.pos*2 <= MAX_N){
            q.push({curr.pos*2, curr.cost});
        }
        if(curr.pos+1 <= MAX_N){
            q.push({curr.pos+1, curr.cost+1});
        }
        if(curr.pos-1 >=  0){
            q.push({curr.pos-1, curr.cost+1});
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> K;
    bfs();

    return 0;
}