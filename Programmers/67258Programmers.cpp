// 보석 쇼핑

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    int lp=0, rp=0;
    set<string> s;
    for(auto gem: gems){
        s.insert(gem);
    }
    int shortest = 987654321;
    int gemTypes = s.size();
    int gemLen = gems.size();
    unordered_map<string, int> buy;
    int lpos=0, rpos=0;
    int buySize = 0;
    while(lp <= rp){
        if(lp == gemLen){
            break;
        }
        if(buySize == gemTypes){
            int temp = shortest;
            shortest = min(shortest, rp-lp);
            // cout << temp;
            if(temp != shortest){
                lpos = lp + 1;
                rpos = rp;
            }
            buy[gems[lp]] -= 1;
            if(buy[gems[lp]] == 0){
                --buySize;
            }
            lp++;
            continue;
        }
        if(rp == gemLen){
            buy[gems[lp]] -= 1;
            if(buy[gems[lp]] == 0){
                break;
            }
            lp++;
            continue;
        }
        buy[gems[rp]] += 1;
        if(buy[gems[rp]] == 1){
            ++buySize;
        }
        ++rp;
    }
    answer.push_back(lpos);
    answer.push_back(rpos);
    return answer;
}