// 카카오프렌즈 컬러링북
#include <vector>
#include <iostream>

#define MAX_N 100

using namespace std;

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
bool visit[MAX_N][MAX_N];
int M, N;

bool checkBound(int r, int c){
    return r < 0 || c < 0 || r >= M || c >= N;
}

int dfs(int num, int r, int c, vector<vector<int>> &picture){
    if(picture[r][c] != num){
        return 0;
    }
    visit[r][c] = true;
    
    int ret = 1;
    for(int i=0; i<4; ++i){
        int nr = r + dir[i][0];
        int nc = c + dir[i][1];
        if(checkBound(nr, nc)){
            continue;
        }
        if(visit[nr][nc]){
            continue;
        }
        if(picture[nr][nc] != num){
            continue;
        }
        ret += dfs(num, nr, nc, picture);
    }
    
    return ret;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    M = m;
    N = n;
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            visit[i][j] = false;
        }
    }
    
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            if(picture[i][j] == 0){
                continue;
            }
            if(visit[i][j]){
                continue;
            }
            max_size_of_one_area = max(max_size_of_one_area, dfs(picture[i][j], i, j, picture));
            ++number_of_area;
        }
    }
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}