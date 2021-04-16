// 오픈채팅방
function solution(record) {
    var answer = [];
    let enterSentence = "님이 들어왔습니다."
    let outSentence = "님이 나갔습니다."
    let dict = {}
    let leaderUid = ''
    record.forEach((sen) => {
        let splitedSen = sen.split(' ')
        if(splitedSen[0] === 'Enter'){
            dict[splitedSen[1]] = splitedSen[2];
        } else if(splitedSen[0] === 'Leave' && splitedSen[1] !== leaderUid){
            return;
        } else {
            dict[splitedSen[1]] = splitedSen[2];
        }
    })
    record.forEach((sen) => {
        let splitedSen = sen.split(' ')
        if(splitedSen[0] === 'Enter'){
            answer.push(dict[splitedSen[1]]+enterSentence)
        } else if(splitedSen[0] === 'Leave' && splitedSen[1] !== leaderUid){
            answer.push(dict[splitedSen[1]]+outSentence)
        } else {
            return;
        }
    })
    return answer;
}