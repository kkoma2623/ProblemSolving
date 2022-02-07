#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> nums;
vector<char> oper;

void getInput(){
    string str; cin >> str;
    string tempNum;
    for(int i=0; i<str.size(); ++i){
        if(str[i] == '-' || str[i] == '+'){
            oper.push_back(str[i]);
            nums.push_back(stoi(tempNum));
            tempNum = "";

            continue;
        }

        tempNum.push_back(str[i]);
    }

    nums.push_back(stoi(tempNum));
}

long long calcNums(){
    long long retNum = nums[0];
    bool found = false;

    for(int i=0; i<oper.size(); ++i){
        if(oper[i] == '-'){
            found = true;
        }
        if(found){
            retNum -= nums[i+1];
        } else{
            retNum += nums[i+1];
        }
    }

    return retNum;
}

void solve(){
    getInput();
    long long minNum = calcNums();
    cout << minNum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}