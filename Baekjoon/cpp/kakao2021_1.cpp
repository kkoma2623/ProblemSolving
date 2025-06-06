#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

map<string, set<string>> m;
map<string, set<string>> repList;
map<string, int> res;
set<string> banBan;

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    for(int i=0; i<report.size(); ++i){
        vector<string> reportId = split(report[i], ' ');
        m[reportId[1]].insert(reportId[0]);
        repList[reportId[0]].insert(reportId[1]);
    }
    
    vector<string> banList;
    for(auto mm: m){
        if(mm.second.size() >= k){
            banList.push_back(mm.first);
            banBan.insert(mm.first);
        }
    }
    for(auto idList: id_list){
        res[idList] = 0;
    }

    for(auto rep: repList){
        vector<string> s1s2;
        set_intersection(rep.second.begin(), rep.second.end(), banBan.begin(), banBan.end(), back_inserter(s1s2));
        res[rep.first] = s1s2.size();
    }

    for(auto idList: id_list){
        answer.push_back(res[idList]);
    }
    
    return answer;
}