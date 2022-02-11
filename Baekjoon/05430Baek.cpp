#include <iostream>
#include <string>
#include <deque>

using namespace std;

deque<char> parseOrder(){
    deque<char> orders;
    string order; cin >> order;
    int numCnt; cin >> numCnt;

    for(int c=0; c<order.size(); ++c){
        if(!orders.empty() && orders.back() == 'R' && order[c] == 'R'){
            orders.pop_back();
            continue;
        }
        orders.push_back(order[c]);
    }

    return orders;
}

// void printDeq(deque<int> &nums){
//     for(auto num : nums){
//         cout << num << ", ";
//     }cout << "\n";
// }

deque<int> parseNumbers(){
    deque<int> nums;
    string numStr; cin >> numStr;

    string tempNum;
    for(int i=1; i<numStr.size(); ++i){
        if(numStr[i] == ']')
            break;
        if(numStr[i] == ','){
            nums.push_back(stoi(tempNum));
            tempNum = "";
            continue;
        }
        tempNum.push_back(numStr[i]);
    }

    if(tempNum != "")
        nums.push_back(stoi(tempNum));

    return nums;
}

void printAC(deque<int> &nums, bool revState){
    // if(nums.empty()){
    //     cout << "error\n";
    //     return;
    // }

    cout << '[';
    if(!revState){
        for(int i=0; i<nums.size(); ++i){
            if(i == nums.size() - 1){
                cout << nums[i];
                break;
            }
            cout << nums[i] << ',';
        }
    } else{
        for(int i=nums.size() - 1; i>=0; --i){
            if(i == 0){
                cout << nums[i];
                break;
            }
            cout << nums[i] << ',';
        }
    }
    cout << "]\n";
}

void doAC(deque<char> &orders, deque<int> &nums){
    bool reverseState = false;

    while(!orders.empty()){
        char order = orders.front();
        orders.pop_front();

        if(order == 'R'){
            reverseState = !reverseState;
            continue;
        }

        if(nums.empty()){
            cout << "error\n";
            return;
        }

        if(reverseState){
            nums.pop_back();
        } else{
            nums.pop_front();
        }
    }

    printAC(nums, reverseState);
}

void solve(){
    int testCases; cin >> testCases;
    while(testCases--){
        deque<char> orders = parseOrder();
        deque<int> nums = parseNumbers();
        doAC(orders, nums);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}