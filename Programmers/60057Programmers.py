def cut(s, n):
    repeatNum = 0
    retS = ""
    lp = 0
    rp = n
    pivotS = s[lp:rp]
    
    while rp <= len(s):        
        if pivotS == s[lp:rp]:
            repeatNum += 1
            lp = rp
            rp += n
            continue
        if repeatNum == 1:
            retS += pivotS
        else:
            retS += str(repeatNum)
            retS += pivotS
        pivotS = s[lp:rp]
        repeatNum = 0

    # print(repeatNum, rp)
    if repeatNum == 1 or repeatNum == 0:            
        retS += pivotS
        if len(s)%n != 0:
            retS += s[lp: len(s)]

        return len(retS)
    else:
        retS += str(repeatNum)
        retS += pivotS
        if len(s)%n != 0:
            retS += s[lp: len(s)]
        # print(retS)
        return len(retS)
    
        

def solution(s):
    answer = cut(s, 1)
    for i in range(2, len(s)//2+1):
        answer = min(answer, cut(s, i))
    
    return answer