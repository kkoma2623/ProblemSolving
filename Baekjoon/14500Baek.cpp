#include <iostream>
#include <vector>

#define MAX_N 500
#define MAX_M 500
#define TETRO_CNT 19

using namespace std;

int room[MAX_N+1][MAX_M+1];
int N, M;
int maxi;
vector<vector<int>> tetro[TETRO_CNT] = {{{1,1,1,1}},
                                {{1},{1},{1},{1}},
                                {{1,1},{1,1}},
                                {{1,0},{1,0},{1,1}},
                                {{1,1,1},{1,0,0}},
                                {{1,1},{0,1},{0,1}},
                                {{0,0,1},{1,1,1}},
                                {{1,0},{1,1},{0,1}},
                                {{0,1,1},{1,1,0}},
                                {{1,1,1},{0,1,0}},
                                {{0,1},{1,1},{0,1}},
                                {{0,1,0},{1,1,1}},
                                {{1,0},{1,1},{1,0}},
                                {{0,1},{1,1},{1,0}},
                                {{1,1,0},{0,1,1}},
                                {{0,1},{0,1},{1,1}},
                                {{1,0,0},{1,1,1}},
                                {{1,1},{1,0},{1,0}},
                                {{1,1,1},{0,0,1}}};

void getInputs(){
    cin >> N >> M;
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            cin >> room[r][c];
        }
    }
}

bool outOfBound(int r, int c){
    return r < 0 || c < 0 || r >= N || c >= M;
}

int returnSum(int r, int c, int tetroNum){
    int tetroR = tetro[tetroNum].size();
    int tetroC = tetro[tetroNum][0].size();
    int sum = 0;
    for(int rr=0; rr<tetroR; ++rr){
        for(int cc=0; cc<tetroC; ++cc){
            if(outOfBound(r+rr,c+cc)) return -1;
            sum += tetro[tetroNum][rr][cc] * room[r+rr][c+cc];
        }
    }

    return sum;
}

void findMaxi(){
    for(int r=0; r<N; ++r){
        for(int c=0; c<M; ++c){
            for(int i=0; i<TETRO_CNT; ++i){
                int tempSum = returnSum(r, c, i);
                maxi = max(maxi, tempSum);
            }
        }
    }
}

void solve(){
    getInputs();
    findMaxi();
    cout << maxi << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}