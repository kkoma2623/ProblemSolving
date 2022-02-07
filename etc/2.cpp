#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

void getInput(vector<string> &card, int cardNums){
    while(cardNums--){
        string temp; cin >> temp;
        card.push_back(temp);
    }
}

void solve(){
    vector<string> card;
    int cardNums; cin >> cardNums;
    getInput(card, cardNums);

    sort(card.begin(), card.end());

    for(auto iter : card){
        cout << (iter) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testCases; cin >> testCases;
    while(testCases--)
        solve();

    return 0;
}