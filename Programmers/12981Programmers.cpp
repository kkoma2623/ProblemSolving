// 영어 끝말잇기
#include <string>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    set<string> s;
    s.insert(words[0]);
    string bef = words[0];
    if(bef.size() == 1){
        answer.push_back(1);
        answer.push_back(1);
        
        return answer;
    }
    for(int i=1; i<words.size(); ++i){
        int sSize = s.size();
        string curr = words[i];

        if(curr.size() == 1){
            answer.push_back(i%n + 1);
            answer.push_back(i/n + 1);
            
            break;
        }
        if(bef[bef.size()-1] != curr[0]){
            answer.push_back(i%n + 1);
            answer.push_back(i/n + 1);
            
            break;
        }
        
        s.insert(curr);
        if(sSize == s.size()){
            answer.push_back(i%n + 1);
            answer.push_back(i/n + 1);
            
            break;
        }
        bef = curr;
    }
    
    if(answer.empty()){
        answer.push_back(0);
        answer.push_back(0);
    }

    return answer;
}