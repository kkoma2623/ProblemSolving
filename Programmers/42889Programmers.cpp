// 실패율
#include <string>
#include <vector>
#include <algorithm>

#define MAX_N 500

using namespace std;

struct strt{
    long long fail;
    long long clear;
    int stage;
};

bool cmp(const strt &lhs, const strt &rhs){
    if(lhs.fail*rhs.clear == rhs.fail*lhs.clear){
        return lhs.stage < rhs.stage;
    }
    
    return lhs.fail*rhs.clear > rhs.fail*lhs.clear;
}

long long failInfo[MAX_N+1];
long long clearInfo[MAX_N+1];

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    for(int i=1; i<=N; ++i){
        for(auto stage: stages){
            if(stage >= i){
                ++clearInfo[i];
            }
            if(stage > N){
                continue;
            }
            if(stage == i){
                ++failInfo[i];
            }
        }
    }
    
    vector<strt> por(N+1);
    for(int i=1; i<=N; ++i){
        por[i] = {failInfo[i], clearInfo[i], i};
    }
    
    sort(por.begin()+1, por.end(), cmp);
    for(int i=1; i<=N; ++i){
        answer.push_back(por[i].stage);
    }
    return answer;
}