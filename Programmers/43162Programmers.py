import sys
sys.setrecursionlimit(2000)

ds = [0]

def _find(n):
    if n == ds[n]:
        return n
    
    ds[n] = _find(ds[n])
    
    return ds[n]

def _union(u, v):
    u = _find(u)
    v = _find(v)
    print(u,':', v)
    if u == v:
        return
    if u < v:
        ds[u] = v
    else:
        ds[v] = u
    
def solution(n, computers):
    answer = 0
    for i in range(1, n+1):
        ds.append(i)

    for i in range(0, len(computers)):
        for j in range(i+1, len(computers[0])):
            if computers[i][j]:
                _union(i+1, j+1)
    
    s = set()
    for i in range(1, len(computers) + 1):
        s.add(_find(i))
    answer = len(s)
    return answer