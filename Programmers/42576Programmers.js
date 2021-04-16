function solution(participant, completion) {
    var answer = '';
    let dict = {};
    participant.forEach((par) => {
        if(dict.hasOwnProperty(par)){
            dict[par] += 1;
        } else {
            dict[par] = 1;
        }
    })
    completion.forEach((comp) => {
        dict[comp] -= 1;
    })
    for(const [key, val] of Object.entries(dict)){
        if(val > 0){
            answer = key
            break;
        }
    }
    
    // console.log(dict)
    return answer;
}