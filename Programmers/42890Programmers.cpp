// 후보키

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <math.h>

#define MAX_C 8

using namespace std;

vector<vector<int>> vec;
vector<long long> uniq;

void makeComb(vector<int> visit, int r, int n, int pos, int colSize){
    
    if(n == r){
        vector<int> temp;
        for(int i=0; i<colSize; ++i){
            temp.push_back(visit[i]);
        }
        vec.push_back(temp);
        
        return;
    }
    
    if(pos > colSize){
        return;
    }
    
    for(int i=pos; i<colSize; ++i){
        if(visit[i]){
            continue;
        }
        visit[i] = 1;
        makeComb(visit, r+1, n, i+1, colSize);
        visit[i] = 0;
    }
}

void isUniq(vector<vector<string>> &relation, int rowSize, int colSize){
    for(int i=0; i<vec.size(); ++i){
        set<string> s;
        
        for(int row=0; row<rowSize; ++row){
            string temp ="";
            for(int j=0; j<colSize; ++j){
                if(vec[i][j] == 0){
                    continue;
                }
                temp += relation[row][j];
                
            }
            s.insert(temp);
        }
        if(s.size() == rowSize){
            long long temp = 0;
            for(int j=0; j<colSize; ++j){
                temp += vec[i][j] * pow(2, j);
            }
            uniq.push_back(temp);
        }
    }
}

bool isRepeat(long long lhs, long long rhs){
    return (lhs&rhs) == lhs;
}

void makeMinimal(){
    for(int i=0; i<uniq.size()-1; ++i){
        for(int j=0; j<uniq.size(); ++j){
            if(i != j && uniq[i] != 0 && isRepeat(uniq[i], uniq[j])){
                uniq[j] = 0;
            }
        }
    }
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    
    const int ROWSIZE = relation.size();
    const int COLSIZE = relation[0].size();

    for(int keys=1; keys<=COLSIZE; ++keys){
        vector<int> arr;
        for(int i=0; i<COLSIZE; ++i){
            arr.push_back(0);
        }
        makeComb(arr, 0, keys, 0, COLSIZE);
    }

    isUniq(relation, ROWSIZE, COLSIZE);
    makeMinimal();
    for(int i=0; i<uniq.size(); ++i){
        // cout << uniq[i] << "\n";
        if(uniq[i] != 0){
            ++answer;
        }
    }
    return answer;
}