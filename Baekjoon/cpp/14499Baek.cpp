#include <iostream>
#include <queue>

#define MAX_N 20
#define MAX_M 20
#define UP 1
#define RI 3
#define LE 4
#define FR 5
#define BA 2
#define BO 6

using namespace std;

int dice[7];
int N, M;
int x, y, k;
int G[MAX_N][MAX_M];
queue<int> order;

bool outOfBound(){
    return x < 0 || y < 0 || x >= N || y >= M;
}

void getInputs(){
    cin >> N >> M >> x >> y >> k;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            cin >> G[r][c];
        }
    }
    for(int i=0; i<k; ++i){
        int temp; cin >> temp;
        order.push(temp);
    }
}

void copyNum(){
    if(G[x][y] == 0){
        G[x][y] = dice[BO];
    } else{
        dice[BO] = G[x][y];
        G[x][y] = 0;
    }
}

void moveEast(){
    int pastDice[7];
    for(int i=0; i<7; ++i){
        pastDice[i] = dice[i];
    }
    dice[UP] = pastDice[4];
    dice[RI] = pastDice[1];
    dice[LE] = pastDice[6];
    dice[FR] = pastDice[5];
    dice[BA] = pastDice[2];
    dice[BO] = pastDice[3];
}

void moveWest(){
    int pastDice[7];
    for(int i=0; i<7; ++i){
        pastDice[i] = dice[i];
    }
    dice[UP] = pastDice[3];
    dice[RI] = pastDice[6];
    dice[LE] = pastDice[1];
    dice[FR] = pastDice[5];
    dice[BA] = pastDice[2];
    dice[BO] = pastDice[4];
}

void moveNorth(){
    int pastDice[7];
    for(int i=0; i<7; ++i){
        pastDice[i] = dice[i];
    }
    dice[UP] = pastDice[5];
    dice[RI] = pastDice[3];
    dice[LE] = pastDice[4];
    dice[FR] = pastDice[6];
    dice[BA] = pastDice[1];
    dice[BO] = pastDice[2];
}

void moveSouth(){
    int pastDice[7];
    for(int i=0; i<7; ++i){
        pastDice[i] = dice[i];
    }
    dice[UP] = pastDice[2];
    dice[RI] = pastDice[3];
    dice[LE] = pastDice[4];
    dice[FR] = pastDice[1];
    dice[BA] = pastDice[6];
    dice[BO] = pastDice[5];
}

void moveDice(int orderNum){
    if(orderNum == 1){
        y += 1;
        if(outOfBound()){
            y -= 1;
            return;
        }
        moveEast();
    }
    if(orderNum == 2){
        y -= 1;
        if(outOfBound()){
            y += 1;
            return;
        }
        moveWest();
    }
    if(orderNum == 3){
        x -= 1;
        if(outOfBound()){
            x += 1;
            return;
        }
        moveNorth();
    }
    if(orderNum == 4){
        x += 1;
        if(outOfBound()){
            x -= 1;
            return;
        }
        moveSouth();
    }

    copyNum();
    cout << dice[UP] << "\n";
}

void solve(){
    getInputs();
    while(!order.empty()){
        int orderNum = order.front(); order.pop();
        moveDice(orderNum);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}