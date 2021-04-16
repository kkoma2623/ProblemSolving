// 경주로 건설
#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define MAX_N 25

using namespace std;

struct pos{
    int r, c;
    int cost;
    int dirNum;
};

int G[MAX_N+1][MAX_N+1];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void bfs(vector<vector<int>> &board){
    queue<pos> q;
    q.push({0, 0, 0, 4});
    int m = board.size();
    int n = board[0].size();
    
    while(!q.empty()){
        pos curr = q.front();
        q.pop();

        if(G[curr.r][curr.c] < curr.cost){
            continue;
        }
        
        G[curr.r][curr.c] = curr.cost;
        for(int i=0; i<4; ++i){
            int nr = curr.r + dir[i][0];
            int nc = curr.c + dir[i][1];
            if(nr < 0 || nc < 0 || nr >= m || nc >= n){
                continue;
            }
            if(board[nr][nc] == 1){
                continue;
            }
            if(curr.dirNum == 4){
                q.push({nr, nc, curr.cost + 100, i});
                continue;
            }
            if(curr.dirNum != i){
                q.push({nr, nc, curr.cost + 600, i});
            } else{
                q.push({nr, nc, curr.cost + 100, i});
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    for(int i=0; i<board.size(); ++i){
        for(int j=0; j<board[0].size(); ++j){
            G[i][j] = 987654321;
        };
    }
    bfs(board);
    
    answer = G[board.size()-1][board[0].size()-1];
    
    return answer;
}