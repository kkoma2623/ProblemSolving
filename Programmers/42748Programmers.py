def solution(array, commands):
    answer = []
    for command in commands:
        i, j, k = command
        tempArr = array[i-1:j]
        tempArr.sort()
        answer.append(tempArr[k-1])
        
    return answer