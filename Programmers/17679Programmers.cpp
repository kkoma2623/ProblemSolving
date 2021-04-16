//프렌즈4블록

#include <string>
#include <vector>

#define MAX_N 30

using namespace std;

int check4[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
char boardG[MAX_N][MAX_N];
bool removeG[MAX_N][MAX_N];

void initRemove(int m, int n){
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            removeG[i][j] = false;
        }
    }
}

bool checkRemove(int r, int c, int m, int n){
    char doll = boardG[r][c];
    if(doll == '0'){
        return false;
    }
    for(int i=1; i<4; ++i){
        int nr = r + check4[i][0];
        int nc = c + check4[i][1];
        
        if(doll != boardG[nr][nc]){
            return false;
        }
    }
    
    return true;
}

void pullBlock(int r, int c){
    if(boardG[r][c] != '0'){
        return;
    }
    
    int nr = r-1;
    if(nr < 0){
        return;
    }

    while(boardG[nr][c] == '0'){
        nr -= 1;
        if(nr < 0){
            return;
        }
    }
    
    char nChar = boardG[nr][c];
    boardG[r][c] = nChar;
    boardG[nr][c] = '0';
}

int removeBlock(int m, int n){
    for(int r=0; r<m-1; ++r){
        for(int c=0; c<n-1; ++c){
            if(boardG[r][c] == '0'){
                continue;
            }
            if(!checkRemove(r, c, m, n)){
                continue;
            }
            
            for(int i=0; i<4; ++i){
                int nr = r + check4[i][0];
                int nc = c + check4[i][1];

                removeG[nr][nc] = true;
            }
        }
    }
    
    int ret = 0;
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            if(removeG[i][j]){
                boardG[i][j] = '0';
                ++ret;
            }
        }
    }
    
    for(int i=m-1; i>=0; --i){
        for(int j=0; j<n; ++j){
            pullBlock(i, j);
        }
    }
    
    return ret;
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            boardG[i][j] = board[i][j];
            removeG[i][j] = false;
        }
    }
    
    int ret = 1;
    while(ret){
        initRemove(m, n);
        ret = removeBlock(m, n);
        answer += ret;
    }
    
    return answer;
}