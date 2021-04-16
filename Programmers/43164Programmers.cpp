// 여행경로
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

map<string, map<string, int>> m;
int totalTickets;

bool dfs(string start, int usedTickets, vector<string> &cityList){
    map<string, int> _m;
    if(usedTickets == totalTickets){
        return true;
    }
    for(auto &ticketInfo: m[start]){
        if(ticketInfo.second <= 0){
            continue;
        }
        
        ticketInfo.second -= 1;
        cityList.push_back(ticketInfo.first);
        bool finish = dfs(ticketInfo.first, usedTickets + 1, cityList);
        if(finish){
            return true;
        }
        ticketInfo.second += 1;
        cityList.pop_back();
    }
    
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    totalTickets = tickets.size();
    for(auto ticket: tickets){
        m[ticket[0]][ticket[1]] += 1;
    }
    
    answer.push_back("ICN");
    dfs("ICN", 0, answer);
    return answer;
}