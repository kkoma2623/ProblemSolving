import sys
import copy
from collections import deque
sys.setrecursionlimit(2000)

dir = [[0, 1], [0, -1], [1, 0], [-1, 0]]

def bfs(board, boardCopy):
    
    maxR = len(board)
    maxC = len(board[0])
    q = deque()
    q.append({'r': 0, 'c': 0, 'cost': 0, 'dirNum': 4})
    
    while len(q):
        curr = q.popleft()
        # print(curr)
        # if nr < 0 or nc < 0 or nr >= maxR or nc >= maxC:
        if boardCopy[curr['r']][curr['c']] < curr['cost']:
            continue
        
        boardCopy[curr['r']][curr['c']] = curr['cost']
        for i in range(0, 4):
            nr = curr['r'] + dir[i][0]
            nc = curr['c'] + dir[i][1]
            if nr < 0 or nc < 0 or nr >= maxR or nc >= maxC:
                continue
            
            if board[nr][nc] == 1:
                continue
            
            if curr['dirNum'] == 4:
                if boardCopy[nr][nc] < curr['cost'] + 100:
                    continue
                q.append({'r': nr, 'c': nc, 'cost': curr['cost'] + 100, 'dirNum': i})
            elif i == curr['dirNum']:
                if boardCopy[nr][nc] < curr['cost'] + 100:
                    continue
                q.append({'r': nr, 'c': nc, 'cost': curr['cost'] + 100, 'dirNum': i})
            else:
                if boardCopy[nr][nc] < curr['cost'] + 600:
                    continue
                q.append({'r': nr, 'c': nc, 'cost': curr['cost'] + 600, 'dirNum': i})
                
    
    
def solution(board):
    boardCopy = [[987654321]*len(board[0]) for _ in range(len(board))]

    bfs(board, boardCopy)
    answer = boardCopy[len(board)-1][len(board[0])-1]
    return answer
