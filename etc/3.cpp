#include <iostream>

#define MAX_N 100000

using namespace std;

int visited[MAX_N+1];
int path[MAX_N+1];
int lastCamp;
//  todayTimes = 휴게소 안들리고 이동한 시간
// todayDist = 오늘 이동 거리
int dfs(int todayTimes, int totalTimes, int pos, int todayDist){
    if(pos > lastCamp){
        // 최종 목적지를 지나가면 안됨
        return -1;
    }
    if(todayDist >= 15 && path[pos] != 3){
        // 최대 이동 거리인 15를 넘었지만 숙박할 수 없다면 안됨
        return -1;
    }
    if(lastCamp == pos){
        // 최종 목적지에 도달하면 여태 소요한 시간 리턴
        return totalTimes + 1;
    }
    if(todayTimes >= 6 && path[pos] == 1){
        // 한 번에 6시간 이상 이동하면 안됨!
        return -1;
    }
    

    int nowCondition = path[pos];
    switch(nowCondition){
        case 1:
            return dfs(todayTimes + 1, totalTimes + 1, pos + 1, todayDist + 1);
        case 2: {
            int noBreakTime = dfs(todayTimes + 1, totalTimes + 1, pos + 1, todayDist + 1);
            int breakTime = dfs(2, totalTimes + 2, pos + 1, todayDist + 1);
            if(noBreakTime != -1){
                return noBreakTime;
            } else{
                return breakTime;
            }
            break;
        }
        case 3:{
            int noSleepTime = dfs(todayTimes + 1, totalTimes + 1, pos + 1, todayDist + 1);
            int sleepTime = dfs(1, totalTimes + 1, pos + 1, 1);
            if(noSleepTime != -1){
                return noSleepTime;
            } else{
                return sleepTime;
            }
            break;
        }
        case 0:
        default:
            return -1;
    }
}

void initPath(){
    for(int i=0; i<MAX_N; ++i){
        path[i] = 0;
    }
}

void getInput(){
    int len; cin >> len;
    initPath();
    for(int i=0; i<len; ++i){
        cin >> path[i];
        if(path[i] == 3){
            lastCamp = i;
        }
    }
}

void solve(){    
    getInput();
    cout << dfs(1, 1, 1, 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int testCases; cin >> testCases;
    for(int i=1; i<=testCases; ++i){
        cout << "#" << i << " ";
        solve(); cout << "\n";
    }

    return 0;
}