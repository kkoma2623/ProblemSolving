# 방금 그곡
def solution(m, musicinfos):
    answer = '(None)'
    m = m.replace('C#', 'c')
    m = m.replace('D#', 'd')
    m = m.replace('F#', 'f')
    m = m.replace('G#', 'g')
    m = m.replace('A#', 'a')
    print(m)
    longTime = 0
    for musicInfo in musicinfos:
        startTime, endTime, title, doraemi = musicInfo.split(',')
        # print(startTime, endTime, title, doraemi)
        doraemi = doraemi.replace('C#', 'c')
        doraemi = doraemi.replace('D#', 'd')
        doraemi = doraemi.replace('F#', 'f')
        doraemi = doraemi.replace('G#', 'g')
        doraemi = doraemi.replace('A#', 'a')
        songTime = len(doraemi)
        startTimeMin, startTimeSec = startTime.split(':')
        endTimeMin, endTimeSec = endTime.split(':')
        
        playSeconds = int(endTimeMin)*60 + int(endTimeSec) - (int(startTimeMin)*60 + int(startTimeSec))
        
        if playSeconds < len(doraemi):
            doraemi = doraemi[:playSeconds]

        lenDoraemi = len(doraemi)
        doraemi2 = ''
        for i in range(0, playSeconds):
            doraemi2 = doraemi2 + doraemi[i % lenDoraemi]

        print(doraemi2)
        
        if m in doraemi2:
            if longTime < playSeconds:
                longTime = playSeconds
                answer = title
                
    return answer