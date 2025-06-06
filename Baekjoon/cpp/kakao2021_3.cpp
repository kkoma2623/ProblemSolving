#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

struct parking{
    string time;
    string num;
    string status;
    int useTime;
    int totalFee;
};

int strToMin(string time){
    int h = stoi(time.substr(0,2));
    int m = stoi(time.substr(3,5));
    
    return h*60 + m;
}

bool comp(parking &lhs, parking &rhs){
    int lTime = strToMin(lhs.time);
    int rTime = strToMin(rhs.time);
    
    return lTime < rTime;
}

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
 
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    map<string, vector<parking>> parks;
    for(auto record: records){
        vector<string> splited = split(record, ' ');
        parking tempS;
        tempS.time = splited[0];
        tempS.num = splited[1];
        tempS.status = splited[2];
        parks[tempS.num].push_back(tempS);
    }
    
    map<string, int> parkTime;
    // for(auto park: parks){
    //     sort(park.second.begin(), park.second.end(), comp);
    // }
    for(auto park: parks){
        parkTime[park.first] = 0;
        if(park.second.size() < 2){
            // no out
            int outTime = strToMin("23:59");
            int inTime = strToMin(park.second[0].time);
            parkTime[park.second[0].num] = outTime - inTime;
        } else{
            int outTime = 0;
            int inTime = 0;
            for(auto v: park.second){
                if(v.status == "IN"){
                    inTime = strToMin(v.time);
                } else{
                    outTime = strToMin(v.time);
                    parkTime[v.num] += outTime - inTime;
                }
            }
            if(park.second.size()%2 == 1){
                outTime = strToMin("23:59");
                parkTime[park.first] += outTime - inTime;
            }
        }
    }
    
    int baseMin = fees[0];
    int baseFee = fees[1];
    int posMin = fees[2];
    int posFee = fees[3];
    for(auto parkT: parkTime){
        // cout << parkT.first << ": " << parkT.second << endl;
        int totalFee = 0;
        int useMin = parkT.second;
        if(baseMin >= useMin){
            answer.push_back(baseFee);
            continue;
        } else{
            totalFee += baseFee;
            int overMin = useMin - baseMin;
            if(overMin % posMin != 0){
                overMin += posMin;
            }
            totalFee += (overMin/posMin)*posFee;
        }
        answer.push_back(totalFee);
    }

    return answer;
}