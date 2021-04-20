// 타겟 넘버
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int dfs(char op, vector<int> &numbers, int pos, int target, int num){
    if(pos == numbers.size()){
        if(target == num){
            // cout << target << " " << num << endl;
            return 1;
        } else{
            return 0;
        }
    }
    
    int currNum = numbers[pos];
    if(op == '-'){
        currNum = -currNum;
    }
    
    int ret = 0;
    // cout << "currNUm " << currNum << endl;
    if(pos == numbers.size()-1){
        ret += dfs('+', numbers, pos+1, target, currNum + num);
    } else{
        ret += dfs('+', numbers, pos+1, target, currNum + num);
        ret += dfs('-', numbers, pos+1, target, currNum + num);
    }
    
    
    return ret;
}

int solution(vector<int> numbers, int target) {
    int answer = dfs('+', numbers, 0, target, 0);
    answer += dfs('-', numbers, 0, target, 0);
    return answer;
}