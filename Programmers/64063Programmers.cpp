// 호텔 방 배정
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<long long, long long> hotel;

long long _find(long long num){
    if(hotel.find(num) == hotel.end() || hotel[num] == 0){
        return num;
    }
    
    return hotel[num] = _find(hotel[num]);
}

void _union(long long num, vector<long long> &ans){    
    long long next = _find(num);
    if(num == next){
        hotel[num] = _find(num+1);
        ans.push_back(num);
        
        return;
    }
    
    _union(next, ans);
}

// void checkIn(long long num, vector<long long> &ans){
//     auto iter = hotel.find(num);
//     if(iter == hotel.end()){
//         hotel[num] = true;
//         ans.push_back(num);
        
//         return;
//     }
    
//     while(hotel.find(num) != hotel.end()){
//         ++num;
//     }
    
//     hotel[num] = true;
//     ans.push_back(num);
// }

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for(auto room: room_number){
        _union(room, answer);
    }
    return answer;
}