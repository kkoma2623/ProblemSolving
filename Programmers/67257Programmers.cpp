// 수식 최대화

#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

char perm[6][3] = {{'*', '+', '-'}, {'*', '-', '+'}, {'+', '*', '-'},
                   {'+', '-', '*'}, {'-', '*', '+'}, {'-', '+', '*'}};

void parsingExpression(string &expression, vector<ll> &nums, vector<char> & oper){
    ll temp = 0;
    for(int i=0; i<expression.size(); ++i){
        int num = expression[i] - '0';
        if(num >= 0 && num <= 9){
            if(i == expression.size() - 1){
                nums.push_back(temp + num);
                return;
            }
            temp += num;
            temp *= 10;
            continue;
        }
        
        temp /= 10;
        nums.push_back(temp);
        oper.push_back(expression[i]);
        temp = 0;
        
    }
}

ll calc(ll temp1, ll temp2, char op){
    switch(op){
        case '*':
            return temp1 * temp2;
        case '+':
            return temp1 + temp2;
        case '-':
            return temp1 - temp2;
        default:
            return 0;
    }
}

void changeVecs(vector<ll> &ans, vector<char> &oper){
    vector<ll> temp;
    vector<char> tempOp;
    for(int i=0; i<oper.size(); ++i){
        if(oper[i] == '0'){
            continue;
        }
        temp.push_back(ans[i]);
        tempOp.push_back(oper[i]);
    }
    temp.push_back(ans[ans.size()-1]);
    temp.swap(ans);
    tempOp.swap(oper);
}

ll ABS(ll num){
    return num > 0 ? num : -num;
}

long long solution(string expression) {
    long long answer = 0;
    ll temp = 0;
    vector<ll> nums;
    vector<char> oper;
    parsingExpression(expression, nums, oper);
    ll maxi = 0;
    for(int i=0; i<6; ++i){
        vector<ll> tempNums = nums;
        vector<char> tempOper = oper;
        for(int j=0; j<3; ++j){
            for(int idx=0; idx<tempOper.size(); ++idx){
                if(tempOper[idx] != perm[i][j]){
                    continue;
                }
                
                ll res = calc(tempNums[idx], tempNums[idx+1], tempOper[idx]);
                tempNums[idx+1] = res;
                tempOper[idx] = '0';
            }
            changeVecs(tempNums, tempOper);
        }
        maxi = max(maxi, ABS(tempNums[0]));
    }
    
    
    return maxi;
}