#include <string>
#include <vector>

#define MAX_N 10

using namespace std;

int N, score;
vector<int> arrow;
vector<int> res;
int arr[MAX_N+1];
bool check = false;

void bfs(int n, int idx){
    if(n > N) return;
    if(idx > MAX_N){
        int myScore = 0;
        int oppoScore = 0;
        if(N - n > 0){
            arr[MAX_N] += N - n;
        }
        for(int i=0; i<=MAX_N; ++i){
            int temp = MAX_N-i;
            if(arr[i] > arrow[i]){
                myScore += temp;
            } else{
                if(arrow[i] != 0){
                    oppoScore += temp;
                }
            }
        }
        
        if(myScore > oppoScore){
            check = true;
            if(score < myScore-oppoScore){
                for(int i=0; i<=MAX_N; ++i){
                    res[i] = arr[i];
                }
                score = myScore - oppoScore;
            } else{
                if(score == myScore - oppoScore){
                    bool isSame = false;
                    for(int i=MAX_N; i>=0; --i){
                        if(res[i] == arr[i]){
                            continue;
                        }
                        if(res[i] < arr[i]){
                            isSame = true;
                        }
                        break;
                    }
                    if(isSame){
                        for(int i=0; i<=MAX_N; ++i){
                            res[i] = arr[i];
                        }
                    }
                }
            }
        }
        if(N-n > 0){
            arr[MAX_N] -= (N-n);
        }
        
        return;
    }
    
    int count = arrow[idx]+1;
    arr[idx] = count;
    bfs(n+count, idx+1);
    arr[idx] = 0;
    
    bfs(n, idx + 1);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> answer;
    N = n;
    for(auto inf: info){
        arrow.push_back(inf);
        res.push_back(0);
    }
    
    bfs(0, 0);
    if(!check){
        answer.push_back(-1);
    } else{
        return res;
    }
    return answer;
}